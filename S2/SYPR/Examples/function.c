/*
 * function.c
 *
 * Beispiel-Programm lokale und globale Variablen
 *
 * Autor: H.Drachenfels
 * Erstellt am: 29.2.2012
 */

#include "function.h"
#include "global.h"

int function(int param)
{
    static int private_global = 1;
    int local = param + 1;
    private_global++;
    global = param + 2;
    return local + private_global;
}

