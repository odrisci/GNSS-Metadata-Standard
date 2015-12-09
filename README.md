# GNSS-Metadata-Standard

ToDo:

1) Figure out whether or not the SampleStream IDs are local to the lane, or global to the entire XML file
   Should we encapsulate the bank of SampleSinks within the LaneInterpreter Object?
   
2) Figure out multi-file processing.

3) Pull the sample-sings out to an exposed function call in main, such that the converter feeds a two-faced
   sample buffer, appearing as a SampleSink within the converter, and as a SampleSource in main, to be fed 
   to a receiver, or a file etc.
     
4) Test various chunk sizes

5) Build for gcc on Ubuntu

6) Test on "other-endian" machine