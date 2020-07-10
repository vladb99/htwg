#
# Makefile
#
# Autor: Vlad Bratulescu
# Erstellt am: 10.07.2020
#

#----------------------------------- Kommando-Variablen
CXX = g++
CXXFLAGS = -g -W -Wall -Weffc++ -Wold-style-cast -std=$(STD) -fpic
CPPFLAGS = -I $(LIBDIR)
LDFLAGS = -L $(LIBDIR)
TEST = -l $(LIBDIR)
RM = rm -f
STD = c++11
SL = ar rvs
DL = -shared

#--------------------------------------- Hilfsvariablen
TARGET = notenspiegel
OBJECTS =  \
	notenspiegel.o
SOURCES = $(OBJECTS:.o=.cpp)
HEADERS = \
	$(LIBDIR)/fachnoten_liste.h \
	$(LIBDIR)/benotung.h \
	$(LIBDIR)/fachnote.h
LIBS = \
	$(LIBDIR)/libaufgabe6.*
LIBDIR = ../lib

#----------------------------------------- Musterregeln
%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

#---------------------------------------- Standardziele
.PHONY: all clean

all: $(TARGET)

clean:
	$(RM) $(TARGET) $(OBJECTS) depend

depend: $(SOURCES) $(HEADERS)
	$(CXX) $(CPPFLAGS) -MM $(SOURCES) > $@

#------------------------- Ziele zur Programmerstellung
$(TARGET): $(OBJECTS) $(LIBDIR)/libaufgabe6.so
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

#-------------------------------------- Abhaengigkeiten
include depend

