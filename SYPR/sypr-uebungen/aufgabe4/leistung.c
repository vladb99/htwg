#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "leistung.h"
#include "spo3_ain2.h"

static void ausgeben_benotet(int note);
static void ausgeben_unbenotet(char status);

bool leistung_einlesen(struct leistung *l)
{
    if (scanf("%20s %d", l->modulname, &(l->n)) == 2)
    {
        l->art = benotet;
    }
    else if (scanf("%c", &(l->b)) == 1)
    {
        l->art = unbenotet;
    }
    else
    {
        return false;
    }

    char* pch;
    pch = strchr(l->modulname, '_');
    while (pch != NULL)
    {
        *pch = ' ';
        pch = strchr(pch + 1, '_');
    }
    return true;
}

void ausgeben(const struct leistung *l)
{
    if (ist_ain2_modul(l->modulname))
    {
        printf("%-*s\t", FELD_GROESSE, l->modulname);
        if (l->art == benotet) {
            printf("L\t");
            ausgeben_benotet(l->n);
        }
        else
        {
            printf("S\t");
            ausgeben_unbenotet(l->b);
        }
    }
    else
    {
        printf("Fehler: %s\n", l->modulname);
    }
}

static void ausgeben_benotet(int note)
{
    if (ist_spo_note(note)) 
    {
        int vk = note / 10;
        int nk = note % 10;
        printf("%d,%d\n", vk, nk);
    }
    else
    {
        printf("Fehler: %d\n", note);
    }
}

static void ausgeben_unbenotet(char status)
{
    switch (status)
    {
        case 'B':
            printf("bestanden\n");
            break;
        case 'N':
            printf("nicht bestanden\n");
            break;
        default:
            printf("Fehler: %c\n", status);
            break;
    }
}
