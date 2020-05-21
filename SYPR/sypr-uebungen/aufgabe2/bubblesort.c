#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

int main(int argc, char *argv[])
{
    srand((unsigned int) time(NULL));

    int n = atoi(argv[1]);
    unsigned long numDigits;
    
    if (argc != 2)
    {
        printf("Aufruf: ./bubblesort Anzahl\n");
        return 1;
    }

    if (n == 0) 
    {
        numDigits = 1;
    }
    else
    {
        // Formel fuer Berechnung Anzahl Ziffern
        numDigits = floor(log10(abs(n))) + 1;
    }

    // Die erste Bedingung vergleicht die Anzahl Ziffern von n mit der Anzahl Zeichen von argv[1]
    // Somit werden Eingaben wie 5-1, 5.1, 5junk, usw. nicht erlaubt
    if ((numDigits != strlen(argv[1]) && n >= 0)) {
        printf("NumberFormatException");
        return 1;
    }

    int *a = (int*) calloc((size_t) n, sizeof (int));
    if (a == NULL)
    {
        printf("Speicherreservierung fehlgeschlagen!\n");
        return 1;
    }

    printf("Bitte %d ganze Zahlen eingeben: ", n);

    for (int i = 0; i < n; ++i)
    {
        if (scanf("%d", &a[i]) != 1)
        {
            a[i] = rand();
            printf("%d\n", a[i]);
        }
    }

    for (int i = n; i > 1; --i)
    {
        for (int j = 0; j < i - 1; ++j)
        {
            if (a[j] > a[j + 1]) {
                int tmp = a[j + 1];
                a[j + 1] = a[j];
                a[j] = tmp;
            }
        }
    }

    printf("Sortierte Zahlenfolge: \n");

    for (int i = 0; i < n; ++i) {
        printf("%d\n", a[i]);
    }

    free(a);
    return 0;
}
