#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include <GnssMetadata/Metadata.h>
#include <GnssMetadata/Xml/XmlProcessor.h>
#include "SampleConverter.h"

//
// ToDo:
// - proper testing of SampleEncoderFunctions::  UniformSymmetric() and TwosCompliment() 
// - use a map for the SampleSink, also try to avoid dragging the sample_bast_t template around
//

int main(int argc, char* argv[])
{

   GnssMetadata::Metadata md;
   GnssMetadata::XmlProcessor xproc;

   if( !xproc.Load( "test.xml", false, md) )
   {
      printf("Could not load metadata. Terminating.\n");
      return -1;
   }
   
   SampleConverter spcv( md );

   spcv.Convert( "../../../data/150408_125245_UTC.dat", 2*1024*1024 );

	return 0;
}

