#
# Makefile
#
# Autor: H.Drachenfels
# Erstellt am: 18.11.2019
#

CXX = g++
STD = c++11
CXXFLAGS = -W -Wall -std=$(STD) -pedantic
CPPFLAGS =
RM = rm -f

TARGET = grusstest
OBJECTS = systemuhr.o testuhr.o
HEADERS = $(OBJECTS:.o=.h)

all: $(TARGET)

clean:
	$(RM) $(TARGET) $(TARGET).o $(OBJECTS)

$(TARGET): $(TARGET).o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $^ -o $@

grusstest.o: grusstest.cpp gruss.h systemuhr.h testuhr.h
systemuhr.o: systemuhr.cpp systemuhr.h
testuhr.o: testuhr.cpp testuhr.h

