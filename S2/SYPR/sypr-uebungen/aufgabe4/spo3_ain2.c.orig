/*
 * spo3_ain2.c
 * 
 * Implementiert aus der Header Datei
 * 
 * Autor: Vlad Bratulescu
 * Erstellt am: 12.06.2020
 */

#include <stdio.h>
#include <stdlib.h>

#include "spo3_ain2.h"
#include <string.h>

bool ist_spo_note(int n)
{
    if (!((n >= 10 && n <= 40 && (n % 10 == 0 || n % 10 == 3 || n % 10 == 7)) || n == 50)) 
    {
        return false;
    }
    return true;
}

bool ist_ain2_modul(const char* m)
{
    if (strcmp(m, "Mathematik 2") != 0 && strcmp(m, "Stochastik") != 0 &&
            strcmp(m, "Programmiertechnik 2") != 0 && strcmp(m, "Systemprogrammierung") != 0 &&
                strcmp(m, "Rechnerarchitekturen") != 0)
    {
        return false;
    }
    return true;
}
