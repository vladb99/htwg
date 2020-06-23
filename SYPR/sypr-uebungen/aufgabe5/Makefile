#
# Makefile
#
# Autor: H.Drachenfels
# Erstellt am: 14.1.2020
#

CXX = g++ #-fno-elide-constructors
CXXFLAGS = -g -W -Wall -Weffc++ -Wold-style-cast -std=$(STD)
CPPCHECK = cppcheck --enable=warning,style --std=$(STD)
STD = c++11

TARGET = notenspiegel
OBJECTS = \
    benotung.o \
    fachnote.o \
    fachnoten_liste.o \

.PHONY: all clean cppcheck

all: $(TARGET)

clean:
	rm -f $(TARGET) $(TARGET).o $(OBJECTS)

$(TARGET): $(TARGET).o $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

cppcheck: $(TARGET).cpp $(OBJECTS:.o=.cpp)
	$(CPPCHECK) $^

benotung.o: benotung.cpp benotung.h
fachnote.o: fachnote.cpp fachnote.h benotung.h
fachnoten_liste.o: fachnoten_liste.cpp fachnoten_liste.h fachnote.h benotung.h
notenspiegel.o: notenspiegel.cpp fachnoten_liste.h fachnote.h benotung.h

