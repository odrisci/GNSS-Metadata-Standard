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


#ifndef CLASS_SampleSink
#define CLASS_SampleSink

#include <stdint.h>

class SampleSink
{
protected:
   bool         mIsOpen;

   virtual bool Open() = 0;

public:
   
   virtual ~SampleSink(){};
  
   virtual void AddSample( int8_t  x ) = 0;
   virtual void AddSample( int16_t x ) = 0;
   virtual void AddSample( int32_t x ) = 0;
   virtual void AddSample( int64_t x ) = 0;
   virtual void AddSample( float   x ) = 0;
   virtual void AddSample( double  x ) = 0;

   virtual void Close() = 0;
   virtual void Flush() = 0;
};

#endif // CLASS_SampleSink
