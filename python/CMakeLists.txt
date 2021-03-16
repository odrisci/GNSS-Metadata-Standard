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

add_custom_target( ReplicatePythonSourceTree ALL ${CMAKE_COMMAND} -P
        ${CMAKE_SOURCE_DIR}/cmake/Modules/ReplicatePythonSourceTree.cmake
            ${CMAKE_CURRENT_BINARY_DIR}
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} )

find_package(Python3 COMPONENTS Interpreter Development)
set(PYBIND11_PYTHON_VERSION ${Python3_VERSION})
find_package(pybind11 CONFIG REQUIRED)

add_subdirectory(sdrx)
