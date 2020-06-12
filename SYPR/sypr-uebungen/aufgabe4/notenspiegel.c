/*
 * notenspiegel.c
 *
 * Liest Fachnamen mit Beurteilung ein und gibt dann einen Notenspiegel aus.
 *
 * Autor: H.Drachenfels
 * Erstellt am: 29.11.2019
 */

#include <stdio.h>
#include <stdlib.h>

#include "spo3_ain2.h"
#include "leistung.h"

#ifdef __unix__
#define EINGABE_ENDE "Strg-D"
#else
#define EINGABE_ENDE "Strg-Z"
#endif

int main(void)
{
    //-------------------------------------------------- Notenspiegel einlesen
    fprintf(stderr,
            "Leistungen eingeben "
            "(Noten zwichen %d und %d, Scheine B oder N, Ende mit %s):\n",
            SPO_BESTE_NOTE, SPO_SCHLECHTESTE_NOTE, EINGABE_ENDE);

    leistung notenspiegel[AIN2_ANZAHL_LEISTUNGEN];
    int n = 0;

    for (;;)
    {
        leistung f;
        if (! leistung_einlesen(&f))
        {
            break;
        }

        if (n >= AIN2_ANZAHL_LEISTUNGEN)
        {
            fprintf(stderr, "Zu viele Eingaben!\n");
            break;
        }

        notenspiegel[n++] = f;
    }

    //-------------------------------------------------- Notenspiegel ausgeben
    printf("NOTENSPIEGEL:\n");
    for (int i = 0; i < n; ++i)
    {
        ausgeben(&notenspiegel[i]);
    }

    return 0;
}

