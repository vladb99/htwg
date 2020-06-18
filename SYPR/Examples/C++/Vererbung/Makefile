#
# Makefile
#
# Autor: H.Drachenfels
# erstellt am: 3.3.2017
#

CXX = g++
CPPFLAGS =
CXXFLAGS = -g -W -Wall -std=c++11

TARGETS = ortstermintest

OBJECTS = datum.o termin.o ortstermin.o

all: $(TARGETS)

clean:
	rm -f $(TARGETS) $(TARGETS:=.o) $(OBJECTS)

ortstermintest: ortstermintest.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

ortstermintest.o: ortstermintest.cpp ortstermin.h  termin.h datum.h
ortstermin.o: ortstermin.cpp ortstermin.h termin.h datum.h
termin.o: termin.cpp termin.h datum.h
datum.o: datum.cpp datum.h

