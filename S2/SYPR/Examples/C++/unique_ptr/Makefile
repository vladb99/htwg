#
# Makefile
#
# Autor: H.Drachenfels
# erstellt am: 15.3.2019
#

CXX = g++
CXXFLAGS = -g -W -Wall -std=c++11

TARGET = unique_ptr_test

all: $(TARGET)

clean:
	rm -f $(TARGET) $(TARGET).o

$(TARGET): $(TARGET).o
	$(CXX) $(CXXFLAGS) -o $@ $<

$(TARGET).o: $(TARGET).cpp htwg_unique_ptr.h

