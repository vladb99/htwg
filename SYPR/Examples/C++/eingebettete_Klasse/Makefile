#
# Makefile
#
# Autor: H.Drachenfels
# erstellt am: 14.3.2019
#

CXX = g++ #-fno-elide-constructors
CXXFLAGS = -g -W -Wall -std=c++11

TARGET = listvar
OBJECTS = intlist.o

all: $(TARGET)

clean:
	rm -f $(TARGET) $(TARGET).o $(OBJECTS)

$(TARGET): $(TARGET).o $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TARGET).o: $(TARGET).cpp intlist.h
intlist.o: intlist.cpp intlist.h

