#
# Makefile
#
# Autor: H.Drachenfels
# Erstellt am: 5.11.2019
#

#-------------------------------------------------------- Kommando-Variablen
CXX = g++ -g
CXXFLAGS = -W -Wall -std=c++11 -pedantic
CPPFLAGS =
RM = rm -f

#------------------------------------------------------------ Hilfsvariablen
TARGET = grusstest
OBJECTS = gruss.o systemuhr.o testuhr.o
HEADERS = $(OBJECTS:.o=.h)

#------------------------------------------------------------- Standardziele
all: $(TARGET)

clean:
	$(RM) $(TARGET) $(TARGET).o $(OBJECTS)

#---------------------------------------------- Ziele zur Programmerstellung
$(TARGET): $(TARGET).o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $^ -o $@

#----------------------------------------------------------- Abhaengigkeiten
grusstest.o: grusstest.cpp gruss.h uhr.h systemuhr.h
gruss.o: gruss.cpp gruss.h uhr.h
systemuhr.o: systemuhr.cpp systemuhr.h uhr.h
testuhr.o: testuhr.cpp testuhr.h uhr.h

