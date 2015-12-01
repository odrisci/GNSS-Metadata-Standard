/**
 * Author: James T. Curran
 *  
 * Copyright(c) 2015 Institute of Navigation
 * http://www.ion.org
 *  
 * This Metadata Converter is free software; you can redistribute it and/or
 * modify it under the terms of the Lesser GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * Lesser GNU General Public License for more details.
 *
 * You should have received a copy of the Lesser GNU General Public License
 * along with Metadata API.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <fstream>
#include "SampleFileSink.h"
#include "SampleConverter.h"
#include "SampleInterpreterFactory.h"


SampleConverter::SampleConverter( GnssMetadata::Metadata& md )
{

   GnssMetadata::LaneList::iterator  lnIt =     md.Lanes().begin();
   GnssMetadata::BlockList::iterator bkIt = lnIt->Blocks().begin();
   GnssMetadata::ChunkList::iterator ckIt = bkIt->Chunks().begin();

   //create the cunk interpreter using the md and info form ckIt
   CreateChunkInterpreter( md, &(*ckIt) );
   
};

SampleConverter::~SampleConverter()
{

   for( std::map<std::string,SampleSink*>::iterator it = mSampleSinks.begin();  it != mSampleSinks.end(); ++it )
      delete it->second;

   for( uint32_t c=0; c<mChunkIntrp.size(); c++ )
      delete mChunkIntrp[c];
};

bool SampleConverter::CreateChunkInterpreter( GnssMetadata::Metadata& md, GnssMetadata::Chunk* chunk  )
{
   
   //create the chunk interpreter and keep a local type-specific reference here for now
   ChunkInterpreter<uint16_t,int8_t>* chunkIntrp = new ChunkInterpreter<uint16_t,int8_t>( static_cast<uint32_t>(chunk->CountWords()) );
   mChunkIntrp.push_back( chunkIntrp );
      
   uint32_t totalOccupiedBitsInChunk = 0;
   
   for(GnssMetadata::LumpList::iterator lpIt = chunk->Lumps().begin(); lpIt != chunk->Lumps().end(); ++lpIt)
   {
      for(GnssMetadata::StreamList::iterator smIt = lpIt->Streams().begin(); smIt != lpIt->Streams().end(); ++smIt)
      {
         //create a sample stream to dump the extracted samples
         printf("Found Stream: %s.int8\n",smIt->toString().c_str());

         //if we don't aleady have a SampleSink for this stream, then create one
         if( mSampleSinks.find( smIt->toString() ) == mSampleSinks.end() )
         {
            std::string fileName = smIt->toString() + ".int8";
            mSampleSinks[smIt->toString()] = new SampleFileSink<int8_t>( fileName  );
         }
         //now create a convenent pointer to this SampleSink
         SampleSink* sampleSink = mSampleSinks[smIt->toString()];

         uint32_t numSmpInterp   =  static_cast<uint32_t>( smIt->RateFactor() );
         uint32_t numPaddingBits = static_cast<uint32_t>( smIt->Packedbits() - numSmpInterp * (chunkIntrp->mSampleInterpFactory.BitWidth( smIt->Format(), smIt->Quantization())) );
         
         std::deque<SampleInterpreter*> streamSplIntrps;
         for( uint32_t si=0; si<numSmpInterp; si++ )
         {
            // take the templated-typed chunkInterpreter and use it to create the appropriate type of sample intepreter
            SampleInterpreter* splIntrp;
            chunkIntrp->mSampleInterpFactory.Create( sampleSink, smIt->Format(), smIt->Encoding(), smIt->Quantization(), splIntrp );
            // and add it to the ordered list
            streamSplIntrps.push_back(splIntrp);
         }
         
         if( numPaddingBits > 0 && ( smIt->Alignment() != GnssMetadata::Stream::StreamAlignment::Undefined) )
         {
            //if necessary, make a padding-interpreter (doing nothing other thank occupying space)
            SampleInterpreter* splIntrp = new SampleInterpreter( numPaddingBits );
            if ( smIt->Alignment() == GnssMetadata::Stream::StreamAlignment::Right )
               streamSplIntrps.push_front(splIntrp);
            else
               streamSplIntrps.push_back(splIntrp);

         }
         
         //now add all of the interpreters for this stream to the chunk-interpreter
         for( std::deque<SampleInterpreter*>::iterator it = streamSplIntrps.begin(); it != streamSplIntrps.end(); ++it )
            mChunkIntrp.back()->AddSampleInterpreter( (*it) );
         
         //keep a count of the total bit-occupation of the chunk
         totalOccupiedBitsInChunk += static_cast<uint32_t>( smIt->Packedbits() );

      } //end iteration over sample-streams
   } //end iteration over lumps

   
   //now apply some padding to fill out the remainder of the chunk bits
   //JTC WARNING - USED INT16_T HARD-CODED FIX ME
   uint32_t numChunkPaddingBits = 8*sizeof(uint16_t)*static_cast<uint32_t>(chunk->CountWords()) - totalOccupiedBitsInChunk;
   if( numChunkPaddingBits > 0 && (chunk->Padding() != GnssMetadata::Chunk::WordPadding::None) )
   {
      bool front =  ( chunk->Padding() == GnssMetadata::Chunk::WordPadding::Head );
      mChunkIntrp.back()->AddSampleInterpreter( new SampleInterpreter( numChunkPaddingBits ), front );
   }


   //
   // ToDo: make meaningful return value
   //
   return true;

};

void SampleConverter::Convert(const char* fileName, const uint32_t bytesToProcess )
{

   //open the file and read one chunk at a time, later we can sort out 
   //buffering this data
   std::ifstream packedFile( fileName, std::ios::binary );
   if( !packedFile.is_open() )
   {
      printf("Could not open file: `%s'.\n",fileName);
      return;
   }
   
   //get the chunk memory from the chunk interpreter
   char*    pChunk = static_cast<char*>( mChunkIntrp.back()->GetChunk() );
   uint32_t nBytes = mChunkIntrp.back()->BytesPerChunk();

   //keep a track on how much has been processed
   uint32_t bytesProcessed = 0;

   //lazy starting hack, file full of simple chunks
   while( packedFile.read( pChunk, nBytes ).gcount() == nBytes )
   {
      mChunkIntrp.back()->Interpret(  );
      bytesProcessed += nBytes;

      if( bytesToProcess != 0 && ( bytesProcessed >= bytesToProcess ) )
         break;

   }

};