#
# Makefile
#
# Autor: H.Drachenfels
# Erstellt am: 25.7.2018
#

#----------------------------------- Kommando-Variablen
CC = gcc
CFLAGS = -W -Wall -std=c11 -pedantic
CPPFLAGS = -I.
RM = rm -f

#--------------------------------------- Hilfsvariablen
TARGET = hallo
OBJECTS = gruss.o
SOURCES = $(TARGET).c $(OBJECTS:.o=.c)
HEADERS = $(OBJECTS:.o=.h)

#----------------------------------------- Musterregeln
%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

#---------------------------------------- Standardziele
.PHONY: all clean

all: $(TARGET)

clean:
	$(RM) $(TARGET) $(TARGET).o $(OBJECTS) depend

depend: $(SOURCES) $(HEADERS)
	$(CC) $(CPPFLAGS) -MM $(SOURCES) > $@

#------------------------- Ziele zur Programmerstellung
$(TARGET): $(TARGET).o $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

#-------------------------------------- Abhaengigkeiten
include depend

