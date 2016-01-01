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

set( api_sources 
    AnyUri.cpp
    AttributedObject.cpp
    Band.cpp
    BaseTypes.cpp
    Block.cpp
    Chunk.cpp
    Cluster.cpp
    CMakeLists.txt
    Comment.cpp
    Date.cpp
    Duration.cpp
    File.cpp
    Frequency.cpp
    Lane.cpp
    Lump.cpp
    Metadata.cpp
    Position.cpp
    Session.cpp
    Source.cpp
    Stream.cpp
    System.cpp
    Xml/AnyUriTranslator.cpp
    Xml/BandTranslator.cpp
    Xml/BlockTranslator.cpp
    Xml/ChunkTranslator.cpp
    Xml/ClusterTranslator.cpp
    Xml/DurationTranslator.cpp
    Xml/FileSetTranslator.cpp
    Xml/FileTranslator.cpp
    Xml/FrequencyTranslator.cpp
    Xml/LaneTranslator.cpp
    Xml/LumpTranslator.cpp
    Xml/MetadataTranslator.cpp
    Xml/OscillatorTranslator.cpp
    Xml/PositionTranslator.cpp
    Xml/RfConfigTranslator.cpp
    Xml/SessionTranslator.cpp
    Xml/SourceTranslator.cpp
    Xml/StreamTranslator.cpp
    Xml/SystemTranslator.cpp
    Xml/Translator.cpp
    Xml/XmlProcessor.cpp
)
	
include_directories(
    ${CMAKE_SOURCE_DIR}/API/source/inc
    ${CMAKE_SOURCE_DIR}/API/source/inc/GnssMetadata
    ${CMAKE_SOURCE_DIR}/API/source/inc/GnssMetadata/Xml
    ${CMAKE_SOURCE_DIR}/API/source/inc/tinyxml2
)

add_library(api ${api_sources})
