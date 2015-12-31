#
#  Author: Cillian O'Driscoll, cillian dot odriscoll (at) gmail dot com
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


set( apix_sources 
    AnyUriTranslator.cpp
    BandTranslator.cpp
    BlockTranslator.cpp
    ChunkTranslator.cpp
    ClusterTranslator.cpp
    CMakeLists.txt
    DurationTranslator.cpp
    FileSetTranslator.cpp
    FileTranslator.cpp
    FrequencyTranslator.cpp
    LaneTranslator.cpp
    LumpTranslator.cpp
    MetadataTranslator.cpp
    OscillatorTranslator.cpp
    PositionTranslator.cpp
    RfConfigTranslator.cpp
    SessionTranslator.cpp
    SourceTranslator.cpp
    StreamTranslator.cpp
    SystemTranslator.cpp
    Translator.cpp
    XmlProcessor.cpp
)
	
include_directories(
    ${CMAKE_SOURCE_DIR}/API/source/inc
    ${CMAKE_SOURCE_DIR}/API/source/inc/GnssMetadata
    ${CMAKE_SOURCE_DIR}/API/source/inc/GnssMetadata/Xml
    ${CMAKE_SOURCE_DIR}/API/source/inc/tinyxml2
)

add_library(apix ${apix_sources} )

