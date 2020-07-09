#!/bin/sh
gcc -c hallo.c
gcc -c gruss.c
gcc hallo.o gruss.o -o hallo
