#
# Makefile
#
# Autor: H.Drachenfels
# Erstellt am: 25.10.2019
#

CC = gcc -g
CFLAGS = -W -Wall -Wvla -std=$(STD) -pedantic
CPPCHECK = cppcheck --enable=warning,style --std=$(STD)
STD = c11

TARGET = bubblesort

.PHONY: all clean cppcheck

all: $(TARGET)

clean:
	$(RM) $(TARGET) $(TARGET).o

cppcheck: $(TARGET).c
	$(CPPCHECK) $<

