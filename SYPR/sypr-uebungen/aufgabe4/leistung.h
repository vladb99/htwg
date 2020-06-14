#include <stdbool.h>

#ifndef LEISTUNG_H
#define LEISTUNG_H

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
static void ausgeben_benotet(int note);
static void ausgeben_unbenotet(char status);

#endif
