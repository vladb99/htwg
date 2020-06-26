#
# Makefile
#
# Autor: H.Drachenfels
# erstellt am: 12.11.2018
#

CXX = g++
CXXFLAGS = -g -W -Wall -std=c++11

TARGET = shared_ptr_test

all: $(TARGET)

clean:
	rm -f $(TARGET) $(TARGET).o

$(TARGET): $(TARGET).o
	$(CXX) $(CXXFLAGS) -o $@ $<

shared_ptr_test.o: shared_ptr_test.cpp htwg_shared_ptr.h

