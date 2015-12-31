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


########################################################################
# Project setup
########################################################################
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(WARNING "In-tree build is bad practice. Try 'cd build && cmake ../' ")
endif(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
cmake_minimum_required(VERSION 2.8)
project(GNSS_METADATA_STANDARD CXX C)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Modules)
file(RELATIVE_PATH RELATIVE_CMAKE_CALL ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})

###############################
# GNSS-SDR version information
###############################
set(THIS_IS_A_RELEASE OFF)   # only related to version name, no further implications.
if(NOT ${THIS_IS_A_RELEASE})
    # Get the current working branch
    execute_process(
        COMMAND git rev-parse --abbrev-ref HEAD
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_BRANCH
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    # Get the latest abbreviated commit hash of the working branch
    execute_process(
        COMMAND git log -1 --format=%h
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_COMMIT_HASH
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
endif(NOT ${THIS_IS_A_RELEASE})

set(VERSION_INFO_MAJOR_VERSION 0)
set(VERSION_INFO_API_COMPAT    0)
if(${THIS_IS_A_RELEASE})
    set(VERSION_INFO_MINOR_VERSION 6)
else(${THIS_IS_A_RELEASE})
    set(VERSION_INFO_MINOR_VERSION 6.git-${GIT_BRANCH}-${GIT_COMMIT_HASH})
endif(${THIS_IS_A_RELEASE})

set(VERSION ${VERSION_INFO_MAJOR_VERSION}.${VERSION_INFO_API_COMPAT}.${VERSION_INFO_MINOR_VERSION})


########################################################################
# Environment setup
########################################################################
include(ExternalProject)

################################################################################
# Checkout cmake version
################################################################################
if(CMAKE_VERSION VERSION_LESS 2.8.8)
      message(STATUS "Your CMake version is too old and does not support some features required by GNSS-SDR. CMake version must be at least 2.8.8. For more information check https://github.com/joakimkarlsson/bandit/issues/40")
      message(FATAL_ERROR "Fatal error: CMake >= 2.8.8 required.")
endif(CMAKE_VERSION VERSION_LESS 2.8.8)


################################################################################
# Checkout compiler version
################################################################################

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
      if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.7)
          message(STATUS "Your GCC version is too old and does not support some C++11 features required by GNSS-SDR. GCC version must be at least 4.7")
          message(FATAL_ERROR "Fatal error: GCC >= 4.7 required.")
      endif(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.7)
endif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")


########################################################################
# Set compiler flags
########################################################################

# Enable C++11 support in GCC
# For "-std=c++0x"  GCC's support for C++11 see http://gcc.gnu.org/projects/cxx0x.html
if(CMAKE_COMPILER_IS_GNUCXX AND NOT WIN32)
     set(MY_CXX_FLAGS "${MY_CXX_FLAGS} -std=c++11 -Wall -Wextra")  #Add warning flags: For "-Wall" see http://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html
endif(CMAKE_COMPILER_IS_GNUCXX AND NOT WIN32)
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(MY_CXX_FLAGS "${MY_CXX_FLAGS} -std=c++11 -stdlib=libc++ -Wno-c++11-narrowing")
    if(CMAKE_BUILD_TYPE MATCHES "Release")
        set(MY_CXX_FLAGS "${MY_CXX_FLAGS} -Wno-unused-private-field")
    endif(CMAKE_BUILD_TYPE MATCHES "Release")
endif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")

if(CMAKE_COMPILER_IS_GNUCXX AND NOT WIN32)
    #http://gcc.gnu.org/wiki/Visibility
    add_definitions(-fvisibility=hidden)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MY_CXX_FLAGS}")


########################################################################
# Add subdirectories (in order of deps)
########################################################################
add_subdirectory(API)
add_subdirectory(Converter)

