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
#ifndef CLASS_SampleConverter
#define CLASS_SampleConverter

#include <stdint.h>
#include <vector>
#include <string>
#include "SampleSink.h"
#include "BlockInterpreter.h"
#include "ChunkInterpreter.h"
#include <GnssMetadata/Metadata.h>

class SampleConverter
{
protected:

   std::map<std::string,SampleSink*> mSampleSinks;
   std::vector<BlockInterpreter*>    mBlockInterp;
  

   //protected member functions, to keep the code clean and clear
   bool CreateChunkInterpreter( GnssMetadata::Metadata& md, GnssMetadata::Chunk* chunk, Chunk** chunkInterp  );

public:
   SampleConverter( GnssMetadata::Metadata& md );
   virtual ~SampleConverter(void);

   void Convert(const char* fileName, const uint32_t bytesToProcess = 0);
 
};


#endif // CLASS_SampleConverter
