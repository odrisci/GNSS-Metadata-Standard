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
#  along with Metadata API.  If not, see <http://www.gnu.org/licenses/>.
# 

CXX     = g++
CCFLAGS = -c -std=c++11 -Wall
AR      = ar
ARFLAGS = rcs

APP             = TestApp
APP_SOURCEDIR   = ../../source/app/
APP_SOURCES     = $(wildcard $(APP_SOURCEDIR)*.cpp)
INSTALLDIR      = ../../install/

XML_SOURCEDIR   = ../../source/lib/tinyxml2/
XML_INCLUDEDIR  = ../../source/inc/tinyxml2/
XML_LIBDIR      = xmllib/
XML_SOURCES     = $(wildcard $(XML_SOURCEDIR)*.cpp) 
XML_SOURCEFILES = $(subst $(XML_SOURCEDIR), ,$(XML_SOURCES)) 
XML_OBJECTS     = $(subst $(XML_SOURCEDIR),$(XML_LIBDIR),$(subst .cpp,.o,$(XML_SOURCES))) 


API_SOURCEDIR   = ../../source/lib/GnssMetadata/
API_INCLUDEDIR  = ../../source/inc/GnssMetadata/
API_LIBDIR      = apilib/
API_SOURCES     = $(wildcard $(API_SOURCEDIR)*.cpp)
API_SOURCEFILES = $(subst $(API_SOURCEDIR), ,$(API_SOURCES)) 
API_OBJECTS     = $(subst $(API_SOURCEDIR),$(API_LIBDIR),$(subst .cpp,.o,$(API_SOURCES))) 

APIX_SOURCEDIR  = ../../source/lib/GnssMetadata/Xml/
APIX_INCLUDEDIR = ../../source/inc/GnssMetadata/Xml/
APIX_SOURCES     = $(wildcard $(APIX_SOURCEDIR)*.cpp)
APIX_SOURCEFILES = $(subst $(APIX_SOURCEDIR), ,$(APIX_SOURCES)) 
APIX_OBJECTS     = $(subst $(APIX_SOURCEDIR),$(API_LIBDIR),$(subst .cpp,.o,$(APIX_SOURCES))) 

all: dir clean $(APP)

lib: dir clean xml_lib api_lib



dir:
	mkdir -p $(API_LIBDIR)
	mkdir -p $(XML_LIBDIR)
	mkdir -p $(INSTALLDIR)

# TINYXML2
xml_lib: $(XML_LIBDIR)libxml.a
	$(AR) $(ARFLAGS) $(XML_LIBDIR)libxml.a $(XML_OBJECTS)

$(XML_LIBDIR)libxml.a: $(XML_SOURCES)
	$(CXX) $(CCFLAGS) -I$(XML_INCLUDEDIR) $(XML_SOURCES)
	mv *.o $(XML_LIBDIR)

# GNSSMETADATA API
api_lib: $(API_LIBDIR)libapi.a
	$(AR) $(ARFLAGS) $(API_LIBDIR)libapi.a $(API_OBJECTS) $(APIX_OBJECTS)

$(API_LIBDIR)libapi.a: $(API_SOURCES)  $(APIX_SOURCES)
	$(CXX) $(CCFLAGS) -I../../source/inc/ -I$(API_INCLUDEDIR) -I$(APIX_INCLUDEDIR) $(API_SOURCES)
	$(CXX) $(CCFLAGS) -I../../source/inc/ -I$(API_INCLUDEDIR) -I$(APIX_INCLUDEDIR) -I$(XML_INCLUDEDIR) $(APIX_SOURCES)
	mv *.o $(API_LIBDIR)


# Test Application
$(APP): api_lib xml_lib
	$(CXX) -I../../source/inc/ -I$(API_INCLUDEDIR) -I$(APIX_INCLUDEDIR) -I$(XML_INCLUDEDIR) $(APP_SOURCES) -L$(API_LIBDIR) -lapi -L$(XML_LIBDIR) -lxml -o $(INSTALLDIR)$(APP)

clean:
	rm  -f $(API_LIBDIR)*.o
	rm  -f $(API_LIBDIR)*.a
	rm  -f $(INSTALLDIR)$(APP)




