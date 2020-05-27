#
# Makefile
#
# Erzeugt separate Dateien mit Praeprozessor-Ausgaben.
#
# Autor: H.Drachenfels
# Erstellt am: 7.11.2019
#

CC = gcc
CFLAGS = -g -W -Wall -std=c11 -pedantic

PREPROCESSOR = $(CC) -E $(CPPFLAGS)
COMPILER = $(CC) -c $(CFLAGS)
LINKER = $(CC) $(LDFLAGS)

OBJECTS = \
  localglobalvar.o \
  function.o \
  global.o \


all: localglobalvar

clean:
	rm -f localglobalvar $(OBJECTS) $(OBJECTS:.o=.i)


localglobalvar: $(OBJECTS)
	$(LINKER) -o localglobalvar $(OBJECTS)


localglobalvar.o: localglobalvar.i
	$(COMPILER) localglobalvar.i

function.o: function.i
	$(COMPILER) function.i

global.o: global.i
	$(COMPILER) global.i


localglobalvar.i: localglobalvar.c function.h global.h
	$(PREPROCESSOR) localglobalvar.c -o localglobalvar.i

function.i: function.c function.h global.h
	$(PREPROCESSOR) function.c -o function.i

global.i: global.c global.h
	$(PREPROCESSOR) global.c -o global.i

