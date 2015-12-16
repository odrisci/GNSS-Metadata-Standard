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


#include "SampleFileSink.h"

template<typename sample_base_t>
bool SampleConverter::Open( GnssMetadata::Metadata& md )
{
   
   if( mIsOpen )
   {
      printf("Error: Already open.\n");
      return false;
   }


   LaneInterpreter* laneInterpreter;
   
   for( GnssMetadata::LaneList::iterator  lnIt = md.Lanes().begin(); lnIt != md.Lanes().end(); ++lnIt)
   {
      //create a lane
      laneInterpreter = new LaneInterpreter;
   
      //populate it with blocks
      BlockInterpreter* blockInterp;
      for( GnssMetadata::BlockList::iterator bkIt = lnIt->Blocks().begin(); bkIt != lnIt->Blocks().end(); ++bkIt )
      {
         //create the block
         CreateBlockInterpreter<sample_base_t>( md, &(*bkIt), &blockInterp );
         //now push the block back into the list
         laneInterpreter->AddBlock( blockInterp );
      }

      //if everything is ok, add it to the list of Lanes
      //JTC ToDo - check that it is ok!
      mLaneInterps.push_back( laneInterpreter );
   }

   //if this worked, then flag the converter as being open
   mIsOpen = true;

   return mIsOpen;

};



template<typename sample_base_t>
bool SampleConverter::CreateBlockInterpreter( GnssMetadata::Metadata& md, GnssMetadata::Block* block, BlockInterpreter** blockInterp )
{
   
   //create a block
   *blockInterp = new BlockInterpreter(
                                       static_cast<uint32_t>( block->Cycles() ),
                                       static_cast<uint32_t>( block->SizeHeader() ),
                                       static_cast<uint32_t>( block->SizeFooter() )
                                       );
      
   for( GnssMetadata::ChunkList::iterator ckIt = block->Chunks().begin(); ckIt != block->Chunks().end(); ++ckIt )
   {
      Chunk* chunk;
      //create the cunk interpreter using the md and info form ckIt
      switch( ckIt->SizeWord() )
      {
      case 1:
         CreateChunkInterpreter< uint8_t, sample_base_t>( md, &(*ckIt), &chunk );
         break;
      case 2:
         CreateChunkInterpreter<uint16_t, sample_base_t>( md, &(*ckIt), &chunk );
         break;
      case 4:
         CreateChunkInterpreter<uint32_t, sample_base_t>( md, &(*ckIt), &chunk );
         break;
      case 8:
         CreateChunkInterpreter<uint64_t, sample_base_t>( md, &(*ckIt), &chunk );
         break;
      default:
         printf("Error: unsupported Chunk::SizeWord(): %ld\n",ckIt->SizeWord());
         break;
      }
      //now add it to the current block
      (*blockInterp)->AddChunk(chunk);
   }
        
   //
   // ToDo: make meaningful return value
   //
   return true;

};



template<typename chunk_t, typename sample_base_t>
bool SampleConverter::CreateChunkInterpreter( GnssMetadata::Metadata& md, GnssMetadata::Chunk* chunk, Chunk** chunkInterp )
{
   
   //create the chunk interpreter and keep a local type-specific reference here for now
   ChunkInterpreter<chunk_t,sample_base_t>* chunkIntrp = new ChunkInterpreter<chunk_t,sample_base_t>( static_cast<uint32_t>(chunk->CountWords()) );
   // assign the address
   *chunkInterp = chunkIntrp;

   uint32_t totalOccupiedBitsInChunk = 0;
   
   for(GnssMetadata::LumpList::iterator lpIt = chunk->Lumps().begin(); lpIt != chunk->Lumps().end(); ++lpIt)
   {
      for(GnssMetadata::StreamList::iterator smIt = lpIt->Streams().begin(); smIt != lpIt->Streams().end(); ++smIt)
      {
         //create a sample stream to dump the extracted samples
         printf("Found Stream: %s\n",smIt->toString().c_str());

         //if we don't aleady have a SampleSink for this stream, then create one
         if( mSampleSinks.find( smIt->toString() ) == mSampleSinks.end() )
         {
            std::string fileName = smIt->toString() + ".dat";
            mSampleSinks[smIt->toString()] = new SampleFileSink<sample_base_t>( fileName );
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
         
         if( numPaddingBits > 0 && ( smIt->Alignment() != GnssMetadata::Stream::Undefined) )
         {
            //if necessary, make a padding-interpreter (doing nothing other thank occupying space)
            SampleInterpreter* splIntrp = new SampleInterpreter( numPaddingBits );
            if ( smIt->Alignment() == GnssMetadata::Stream::Right )
               streamSplIntrps.push_front(splIntrp);
            else
               streamSplIntrps.push_back(splIntrp);

         }
         
         //now add all of the interpreters for this stream to the chunk-interpreter
         for( std::deque<SampleInterpreter*>::iterator it = streamSplIntrps.begin(); it != streamSplIntrps.end(); ++it )
            chunkIntrp->AddSampleInterpreter( (*it) );
         
         //keep a count of the total bit-occupation of the chunk
         totalOccupiedBitsInChunk += static_cast<uint32_t>( smIt->Packedbits() );

      } //end iteration over sample-streams
   } //end iteration over lumps

   
   //now apply some padding to fill out the remainder of the chunk bits
   uint32_t numChunkPaddingBits = 8*sizeof(chunk_t)*static_cast<uint32_t>(chunk->CountWords()) - totalOccupiedBitsInChunk;
   if( numChunkPaddingBits > 0 && (chunk->Padding() != GnssMetadata::Chunk::None) )
   {
      bool front =  ( chunk->Padding() == GnssMetadata::Chunk::Head );
      chunkIntrp->AddSampleInterpreter( new SampleInterpreter( numChunkPaddingBits ), front );
   }
   
   //
   // ToDo: make meaningful return value
   //
   return true;

};

