#
#  Author: James T. Curran
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
#  along with Metadata CNV.  If not, see <http://www.gnu.org/licenses/>.
# 

CXX     = g++
CCFLAGS = -c -std=c++11 -Wall
AR      = ar
ARFLAGS = rcs

API_INCS        = ../../../API/source/inc/ -I../../../API/source/inc/GnssMetadata -I../../../API/source/inc/GnssMetadata/Xml -I../../../API/source/inc/tinyxml2 
API_LIBDIR      = ../../../API/ide/make/apilib
XML_LIBDIR      = ../../../API/ide/make/xmllib

APP             = TestApp
APP_SOURCEDIR   = ../../source/app/
APP_SOURCES     = $(wildcard $(APP_SOURCEDIR)*.cpp)
INSTALLDIR      = ../../install/

CNV_SOURCEDIR   = ../../source/lib/
CNV_INCLUDEDIR  = ../../source/inc/
CNV_LIBDIR      = cnvlib/
CNV_SOURCES     = $(wildcard $(CNV_SOURCEDIR)*.cpp)
CNV_SOURCEFILES = $(subst $(CNV_SOURCEDIR), ,$(CNV_SOURCES)) 
CNV_OBJECTS     = $(subst $(CNV_SOURCEDIR),$(CNV_LIBDIR),$(subst .cpp,.o,$(CNV_SOURCES))) 



all: dir clean $(APP)

lib: dir clean cnv_lib

dir:
	mkdir -p $(CNV_LIBDIR)
	mkdir -p $(INSTALLDIR)

# Converter
cnv_lib: $(CNV_LIBDIR)libcnv.a
	$(AR) $(ARFLAGS) $(CNV_LIBDIR)libcnv.a $(CNV_OBJECTS) $(CNVX_OBJECTS)

$(CNV_LIBDIR)libcnv.a: $(CNV_SOURCES)  
	$(CXX) $(CCFLAGS) $(API_INCS) -I$(CNV_INCLUDEDIR) $(CNV_SOURCES)
	mv *.o $(CNV_LIBDIR)

# GnssMetadata lib
api_lib: 
	cd ../../../API/ide/make/ && $(MAKE) lib

# Test Application
# cnv_lib api_lib
$(APP): 
	$(CXX) -I$(API_INCS) -I../../source/inc/ -I$(CNV_INCLUDEDIR) $(APP_SOURCES) -L$(CNV_LIBDIR) -lcnv -L$(API_LIBDIR) -lapi -L$(XML_LIBDIR) -lxml -o $(INSTALLDIR)$(APP)

clean:
	rm  -f $(CNV_LIBDIR)*.o
	rm  -f $(CNV_LIBDIR)*.a
	rm  -f $(INSTALLDIR)$(APP)




