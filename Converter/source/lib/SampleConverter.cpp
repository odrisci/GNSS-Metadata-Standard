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


SampleConverter::SampleConverter( ):
mIsOpen(false)
{

   
      
};

SampleConverter::~SampleConverter()
{

   //just check that it has been closed
   Close();

};

void SampleConverter::Close()
{

   if( mIsOpen )
   {
      for( std::map<std::string,SampleSink*>::iterator it = mSampleSinks.begin();  it != mSampleSinks.end(); ++it )
         delete it->second;

      //delete the lane data
      for( std::vector<LaneInterpreter*>::iterator It = mLaneInterps.begin(); It != mLaneInterps.end(); ++It )
         delete (*It);
   
   }
   mIsOpen = false;
};


void SampleConverter::Convert(const char* fileName, const uint32_t bytesToProcess )
{

   if( !mIsOpen )
   {
      printf("Error: no file open - Terminating.\n[Did you forget to call SampleConverter::Open( GnssMetadata::Metadata&)?].\n )");
      return;
   }

   //
   //
   // So we have a little work to do here, such that the LaneInterpreter looks in the correct file
   // Steps to take:
   //     - Upon the Open() call, we should assign an input file to the LaneInterpreter
   //     - maybe it can actually be opened there too, as an extra check
   //     - when we get here, we can simply pull out the ifstream& from LaneInterpreter* 
   //     - and, of course, iterate over all of the LaneInterpreters...
   //



   //open the file and read one chunk at a time, later we can sort out 
   //buffering this data
   std::ifstream packedFile( fileName, std::ios::binary );
   if( !packedFile.is_open() )
   {
      printf("Could not open file: `%s'.\n",fileName);
      return;
   }
   
   uint32_t bytesProcessed = 0;
   
   if( mLaneInterps.size() == 0 )
   {
      printf("No Lanes found. Terminating.\n");
      return;
   }

   //for now, just decode the first Lane
   LaneInterpreter* laneInterpreter= mLaneInterps.front();
   
   bool readBlockOK = false;
   do
   {
   
      for( std::vector<BlockInterpreter*>::iterator It = laneInterpreter->Blocks().begin(); It != laneInterpreter->Blocks().end(); ++It )
      {
         BlockInterpreter* block = (*It);
         //read the entire block
         do
         {
            readBlockOK = block->Interpret( packedFile, bytesProcessed, bytesToProcess );
         }
         while( readBlockOK );
      }

   }
   while( readBlockOK );


};