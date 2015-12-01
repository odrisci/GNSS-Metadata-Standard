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
 
#include "EncoderFunctions.h"
#include "FormatFunctions.h"


template<typename chunk_t, typename sample_base_t>
SampleInterpreterFactory<chunk_t,sample_base_t>::SampleInterpreterFactory()
{
   
   // "introduce" the EncoderFunctions to the Factory
   mEncoderFunctionMap[ "SIGN" ] = &SampleEncoderFunctions::Sign;
   mEncoderFunctionMap[ "SM" ]   = &SampleEncoderFunctions::SignMagnitude;
   mEncoderFunctionMap[ "BIN" ]  = &SampleEncoderFunctions::OffsetBinary;
   mEncoderFunctionMap[ "INT" ]  = &SampleEncoderFunctions::TwosCompliment;

   // "introduce" the FormatFunctions to the Factory
   mFormatFunctionMap[ GnssMetadata::Stream::SampleFormat::IF   ] = &SampleFormatFunctions::IF<chunk_t,sample_base_t>;
   mFormatFunctionMap[ GnssMetadata::Stream::SampleFormat::IFn  ] = &SampleFormatFunctions::IFn<chunk_t,sample_base_t>;
   mFormatFunctionMap[ GnssMetadata::Stream::SampleFormat::IQ   ] = &SampleFormatFunctions::IQ<chunk_t,sample_base_t>;
   mFormatFunctionMap[ GnssMetadata::Stream::SampleFormat::IQn  ] = &SampleFormatFunctions::IQn<chunk_t,sample_base_t>;
   mFormatFunctionMap[ GnssMetadata::Stream::SampleFormat::InQ  ] = &SampleFormatFunctions::InQ<chunk_t,sample_base_t>;
   mFormatFunctionMap[ GnssMetadata::Stream::SampleFormat::InQn ] = &SampleFormatFunctions::InQn<chunk_t,sample_base_t>;
   mFormatFunctionMap[ GnssMetadata::Stream::SampleFormat::IQ   ] = &SampleFormatFunctions::IQ<chunk_t,sample_base_t>;
   mFormatFunctionMap[ GnssMetadata::Stream::SampleFormat::QIn  ] = &SampleFormatFunctions::QIn<chunk_t,sample_base_t>;
   mFormatFunctionMap[ GnssMetadata::Stream::SampleFormat::QnI  ] = &SampleFormatFunctions::QnI<chunk_t,sample_base_t>;
   mFormatFunctionMap[ GnssMetadata::Stream::SampleFormat::QnIn ] = &SampleFormatFunctions::QnIn<chunk_t,sample_base_t>;

};

template<typename chunk_t, typename sample_base_t>
SampleInterpreterFactory<chunk_t,sample_base_t>::~SampleInterpreterFactory()
{


};

template<typename chunk_t, typename sample_base_t>
bool SampleInterpreterFactory<chunk_t,sample_base_t>::Create(
                     SampleSink* sampleSink,
                     const GnssMetadata::Stream::SampleFormat& fmt,
                     const std::string&  enc,
                     const uint8_t& qnt, 
                     SampleInterpreter* &smplIntrp
                     )
{
   
   //make sure that we can create the sample interpreter
   if( mEncoderFunctionMap.find( enc ) == mEncoderFunctionMap.end() )
   {
      printf("Error: no support for `%s' encoder.",enc.c_str());
      return false;
   }
   if( mFormatFunctionMap.find( fmt ) == mFormatFunctionMap.end() )
   {
      printf("Error: no support for format type (%d).",fmt);
      return false;
   }

   smplIntrp = new SinkedSampleInterpreter<uint16_t,sample_base_t>( 
                        BitWidth( fmt, qnt ), 
                        mEncoderFunctionMap[enc], 
                        mFormatFunctionMap[fmt],
                        sampleSink 
                     );

   return true;

};

template<typename chunk_t, typename sample_base_t>
uint32_t SampleInterpreterFactory<chunk_t,sample_base_t>::BitWidth( const GnssMetadata::Stream::SampleFormat& fmt, const size_t& qnt )
{

   //move to static function of a factory later?
   switch( fmt )
   {
      case GnssMetadata::Stream::SampleFormat::IF  :
      case GnssMetadata::Stream::SampleFormat::IFn :
         return static_cast<uint32_t>(qnt);
      default:
         return 2 * static_cast<uint32_t>(qnt);
   }

};

