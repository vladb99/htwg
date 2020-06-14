/*
 * leistung.h
 *
 * Definiert eine Leistung als struct und Methoden, die die Leistung einlesen und ausgeben
 *
 * Autor: Vlad Bratulescu
 * Erstellt am: 12.06.2020
 */

#include <stdbool.h>

#ifndef LEISTUNG_H
#define LEISTUNG_H

#define STR_EVALUATE(x) #x
#define STRINGIFY(x) STR_EVALUATE(x)
#define FELD_GROESSE 20

enum leistungsart {benotet, unbenotet};
struct leistung
{
    char modulname[FELD_GROESSE + 1];
    enum leistungsart art;
    union
    {
        int n;
        char b;
    };
};
typedef struct leistung leistung;

bool leistung_einlesen(struct leistung *l);
void ausgeben(const struct leistung *l);

#endif
