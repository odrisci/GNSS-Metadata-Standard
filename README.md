# GNSS-Metadata-Standard

ToDo:

1) Figure out whether or not the SampleStream IDs are local to the lane, or global to the entire XML file
   Should we encapsulate the bank of SampleSinks within the LaneInterpreter Object?
   
2) Tidy the templating of the SampleStreams, should the final sample-type (sample_base_t) be determined in
   main, or on a per-stream basis. Do we envisage that some streams may have different sample-types, some
   using lower integer widths than others?
   
3) Figure out multi-file processing.

4) Pull the sample-sings out to an exposed function call in main, such that the converter feeds a two-faced
   sample buffer, appearing as a SampleSink within the converter, and as a SampleSource in main, to be fed 
   to a receiver, or a file etc.
   
   
5) Add functionality to handle Chunk Shift-Direction variable. This can be implemented as an optional 
   reversal of the chunk array once it is read, such that the remainder of the code alwyas processes
   the chunk arrray in a shift-left manner. 