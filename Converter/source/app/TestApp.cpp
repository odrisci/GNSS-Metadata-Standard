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
#include "EndianFunctions.h"

int main(int argc, char* argv[])
{
 
   GnssMetadata::Metadata md;
   GnssMetadata::XmlProcessor xproc;

   if( !xproc.Load( "../../../data/150408_125245_UTC.xml", false, md) )
   {
      printf("Could not load metadata. Terminating.\n");
      return -1;
   }
   
   //ToDo (maybe) create a SampleSink Repository here, and pass a reference to SampleConverter
   // - sample converter creates instances of SampleSink, by name, ans stores pointer
   // - the Repo here will `keep' them, share them with others, and delete them
   // - the converter will only `feed' them
   // - maybe they are presented as `sources' to some receievr, maybe they just dump to file...
   
   SampleConverter spcv;

   //open the Metadata Converter
   // - the template type defines the converted file type
   // - the argument defines the metadata
   spcv.Open<int8_t>( md );

   //perform the conversion
   spcv.Convert( "../../../data/150408_125245_UTC.dat", 1024*1024 );

   //close the converter
   spcv.Close();



	return 0;
}

