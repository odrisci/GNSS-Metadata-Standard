#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#ifdef _WIN32
   #include <direct.h>
#elif defined __linux__
   #include <sys/stat.h>
   #include <unistd.h>
#endif

#include <iostream>

#include <GnssMetadata/Metadata.h>
#include <GnssMetadata/Xml/XmlProcessor.h>
#include "SampleConverter.h"

//
// ToDo:
// - proper testing of SampleEncoderFunctions::  UniformSymmetric() and TwosCompliment() 
// - use a map for the SampleSink, also try to avoid dragging the sample_bast_t template around
//
#include "EndianFunctions.h"


// process triple frequency data from JRC
int processJrcData( void )
{
	
   GnssMetadata::Metadata md;
   GnssMetadata::XmlProcessor xproc;

   if( !xproc.Load( "150408_125245_UTC.xml", false, md) )
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
   // > tested int8_t, int16_t, int32_t, int64_t, float, double
   spcv.Open<int8_t>( md );

   //perform the conversion
   spcv.Convert( 1024*1024 );

   //close the converter
   spcv.Close();

   return 0;
}



// process dual frequency data from IFEN
int processIfenData( void )
{
   GnssMetadata::Metadata md;
   GnssMetadata::XmlProcessor xproc;

   if( !xproc.Load( "RoofTop.setx", false, md) )
   {
      printf("Could not load metadata. Terminating.\n");
      return -1;
   }
   
   SampleConverter spcv;

   spcv.Open<int8_t>( md );

   //perform the conversion 
   spcv.Convert( 1024*1024 ); 

   //close the converter
   spcv.Close();

   return 0;
}


// process triple frequency data from Fraunhofer
int processFhGData( void )
{
   GnssMetadata::Metadata md;
   GnssMetadata::XmlProcessor xproc;

   if( !xproc.Load( "L125_III1b_15s.usbx", false, md) )
   {
      printf("Could not load metadata. Terminating.\n");
      return -1;
   }
   
   SampleConverter spcv;

   spcv.Open<int8_t>( md );

   //perform the conversion 
   spcv.Convert( 1024*1024 ); 

   //close the converter
   spcv.Close();

   return 0;
}


int main(int argc, char* argv[])
{
	int res;
	
	try
	{
		// process JRC data
		std::cout << "JRC data case\n";
		std::cout << "-------------\n";
		chdir( "JRC" );
		res = processJrcData( );
		std::cout << "Result: " << (res==0?"ok":"failed") << "\n\n";
		chdir( ".." );

		// process IFEN data
		std::cout << "IFEN data case\n";
		std::cout << "--------------\n";
		chdir( "IFEN" );
		res = processIfenData( );
		std::cout << "Result: " << (res==0?"ok":"failed") << "\n\n";
		chdir( ".." );

		// process Fraunhofer data
		std::cout << "FHG data case\n";
		std::cout << "-------------\n";
		chdir( "FHG" );
		res = processFhGData( );
		std::cout << "Result: " << (res==0?"ok":"failed") << "\n\n";
		chdir( ".." );

	}
	catch ( GnssMetadata::ApiException &e)
	{
		std::cout << "caught API exception: " << e.what( ) << "\n";
	} 
	catch (std::exception &e)
	{
		std::cout << "caught exception: " << e.what( ) << "\n";
	}
	catch( ... )
	{
		std::cout << "unknown exception\n";
	}
		return 0;
}

