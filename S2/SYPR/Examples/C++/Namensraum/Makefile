#
# Makefile
#
# Autor: H.Drachenfels
# erstellt am: 24.6.2011
#

CXX = g++
CPPFLAGS =
CXXFLAGS = -g -W -Wall -std=c++98 -pedantic

TARGET = enumvar

all: $(TARGET)

clean:
	rm -f $(TARGET) $(TARGET).o

$(TARGET): $(TARGET).o
	$(CXX) $(CXXFLAGS) $^ -o $@

enumvar.o: enumvar.cpp month.h

