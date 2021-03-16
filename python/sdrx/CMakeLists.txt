#
#  Author: Cillian O'Driscoll, cillian dot odriscoll (at) gmail dot com
#
#  Based on the root CMakeLists.txt file of the gnss-sdr project:
#  http://github.com/gnss-sdr/gnss-sdr
#
#  Copyright(c) 2015 Institute of Navigation
#  http://www.ion.org
#   
#  This Metadata Converter is free software; you can redistribute it and/or
#  modify it under the terms of the Lesser GNU General Public License
#  as published by the Free Software Foundation; either version 3
#  of the License, or (at your option) any later version.
#  
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  Lesser GNU General Public License for more details.
# 
#  You should have received a copy of the Lesser GNU General Public License
#  along with Metadata API.  If not, see <http://www.gnu.org/licenses/>.
# 

set( SDRX_CPP_SOURCES
    ./bindings/any_uri.cc
    ./bindings/band.cc
    ./bindings/block.cc
    ./bindings/chunk.cc
    ./bindings/date.cc
    ./bindings/duration.cc
    ./bindings/file.cc
    ./bindings/frequency.cc
    ./bindings/front_end.cc
    ./bindings/lane.cc
    ./bindings/lump.cc
    ./bindings/metadata.cc
    ./bindings/position.cc
    ./bindings/sdrx.cc
    ./bindings/session.cc
    ./bindings/sample_stream_info.cc
    ./bindings/stream.cc
    ./bindings/system.cc
    )

pybind11_add_module(sdrx_cpp_api ${SDRX_CPP_SOURCES})
target_link_libraries(sdrx_cpp_api api cnv xml)

