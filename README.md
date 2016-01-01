# GNSS-Metadata-Standard

ToDo:

1) Figure out whether or not the SampleStream IDs are local to the lane, or global to the entire XML file
   Should we encapsulate the bank of SampleSinks within the LaneInterpreter Object?
   
2) Figure out multi-file processing - specifically: address COMMENT on line 72 of SampleConverter.cpp

3) Pull the sample-sings out to an exposed function call in main, such that the converter feeds a two-faced
   sample buffer, appearing as a SampleSink within the converter, and as a SampleSource in main, to be fed 
   to a receiver, or a file etc.
     
4) Test various chunk sizes

6) Test on "other-endian" machine


## CMake Build Guide

CMake provides a mechanism for managing build processes on different
platforms and using different build tools. The GnssMetadata build system
has been tested on the following build systems:

    1. Unix Makefile 
    2. Windows Microsoft Visual Studio 2015 Community Edition

It is recommended to keep the build system and source trees separate. A
standard approach is to create a ``build`` folder in the project root:

```sh
$ mkdir build
```

Then use CMake to generate the project build artefacts. For example, for
a Debug build using Unix Makefiles:

```sh
$ cd build
$ cmake -DCMAKE_BUILD_TYPE=Debug ../
$ make
```

When using Visual Studio 2015 on Windows, execute the following on a command
prompt:

```dos
> cd build
> cmake -G "Visual Studio 14 2015"
```

This will generate a Visual Studio solution ``GnssMetadata.sln`` in the
``build`` folder. This solution can then be opened in Visual Studio as
normal. Note however that adding files/projects to the solution will not
update the source ``CMakeLists.txt`` file. Note that the command above may need to be adjusted
for different versions of Visual Studio, see [here](https://cmake.org/cmake/help/v3.1/manual/cmake-generators.7.html)
for details. A full list of available generators can be seen by running:

```dos
> cmake -h
```

Do _not_ add the ``build`` folder, or any of its contents, to the source
control system. Only the ``CMakeLists.txt`` files are under version
control, all the relevant project files for each of the build systems
are automatically derived from the ``CMakeLists.txt`` files, and are
automatically updated when these files are updated.



