/*
 * localglobalvar.c
 *
 * Beispiel-Programm lokale und globale Variablen
 *
 * Autor: H.Drachenfels
 * Erstellt am: 25.2.2015 / 10.11.2017 (C11)
 */

#include "function.h"
#include "global.h"

int main(void)
{
    int local = 1 ;

    local = function(local);    // local wird 4
    local = function(global);  // local wird 7

    return 0;
}

