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

#ifndef CLASS_SampleFileSink
#define CLASS_SampleFileSink

#include <fstream>
#include <string>

#include "SampleSink.h"


#define BASE_BUFFER_SIZE_IN_BYTES 1024 * 1024

template<typename sample_base_t>
class SampleFileSink : public SampleSink
{

protected:
   sample_base_t* mSampleBuffer;
   unsigned int   mBufferSize;
   unsigned int   mIndexOfNextSample;
   unsigned int   mRequestedNumberOfSamplesPerBuffer;

   std::string    mFileName;
   std::ofstream  mSampleFile;

   bool Open();
   void DoAddSample( sample_base_t x );
   
public:
   SampleFileSink(std::string fileName, unsigned int numSamplesPerBuffer = BASE_BUFFER_SIZE_IN_BYTES);
   virtual ~SampleFileSink(void);

   // This is a little ugly, but accommodates the parsing of multiple SampleFileSinks, which
   // have different template arguments, in one container. Hopefully the optimizer can take 
   // care of removing the extra function calls. Is there a better way?
   virtual void AddSample( int8_t  x ){ DoAddSample( static_cast<sample_base_t>( x ) ); };
   virtual void AddSample( int16_t x ){ DoAddSample( static_cast<sample_base_t>( x ) ); };
   virtual void AddSample( int32_t x ){ DoAddSample( static_cast<sample_base_t>( x ) ); };
   virtual void AddSample( int64_t x ){ DoAddSample( static_cast<sample_base_t>( x ) ); };
   virtual void AddSample( float   x ){ DoAddSample( static_cast<sample_base_t>( x ) ); };
   virtual void AddSample( double  x ){ DoAddSample( static_cast<sample_base_t>( x ) ); };

   void Flush();
   void Close();
   
};

#include "SampleFileSink.hpp"

#endif // CLASS_SampleFileSink

