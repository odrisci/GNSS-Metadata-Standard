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

#ifndef CLASS_SampleInterpreter
#define CLASS_SampleInterpreter
#include "SampleSink.h"

//a simple emply handle class
class SampleInterpreter
{
protected:
   uint32_t mBitWidth;
public:
   SampleInterpreter( const uint32_t bitWidth ) :
   mBitWidth(bitWidth)
   {};
   virtual ~SampleInterpreter(){};
   virtual void    SetChunkOffset(  const uint32_t chunkOffsetInBits ){};
   virtual void    Interpret( const void* vChunk ) const{};
   virtual uint32_t BitWidth() const { return mBitWidth; };
};

#endif //CLASS_SampleInterpreter


