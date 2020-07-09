# Makefile simple.mak

hallo: hallo.o gruss.o
	gcc hallo.o gruss.o -o hallo

hallo.o: hallo.c gruss.h
	gcc -c hallo.c

gruss.o: gruss.c gruss.h
	gcc -c gruss.c

