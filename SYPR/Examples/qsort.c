/*
 * qsort.c
 *
 * Liest ganze Zahlen ein und sortiert sie mit qsort.
 * (siehe zum Vergleich bubblesort.c)
 *
 * Autor: H.Drachenfels
 * Erstellt am: 25.2.2015 / 10.11.2017 (C11)
 */

#include <stdio.h>
#include <stdlib.h>  // qsort

int intcmp(const void *p, const void *q);

int main(void)
{
    //----------------------------------------------- Feldgroesse einlesen
    printf("Anzahl zu sortierender Werte eingeben:\n");
    int int_array_size;
    if (scanf("%d", &int_array_size) != 1)
    {
        fprintf(stderr, "Eingabefehler!\n");
        return 1;
    }

    //---------------------------------------------------- Zahlen einlesen
    int *int_array = malloc(sizeof (int) * int_array_size);
    printf("%d ganze Zahlen eingeben:\n", int_array_size);

    for (int i = 0; i < int_array_size; ++i)
    {
        if (scanf("%d", &int_array[i]) != 1)
        {
            fprintf(stderr, "Eingabefehler!\n");
            return 1;
        }
    }

    //--------------------------------------------------- Zahlen sortieren
    qsort(int_array, int_array_size, sizeof (int), intcmp);

    //---------------------------------------------------- Zahlen ausgeben
    printf("Sortierte Zahlenfolge:\n");

    for (int i = 0; i < int_array_size; ++i)
    {
        printf("%d ", int_array[i]);
    }

    printf("\n");

    //----------------------------------------------------- Feld freigeben
    free(int_array);

    return 0;
}

/*
 * intcmp
 *
 * Vergleichsfunktion fuer qsort muss liefern:
 * > 0, wenn der erste Wert groesser ist
 * < 0, wenn der erste Wert kleiner ist
 * 0, wenn beide Werte gleich sind
 */
int intcmp(const void *p, const void *q)
{
    const int *left = (const int *) p;
    const int *right = (const int *) q;

    if (*left > *right) return 1;
    if (*left < *right) return -1;
    return 0;
}

