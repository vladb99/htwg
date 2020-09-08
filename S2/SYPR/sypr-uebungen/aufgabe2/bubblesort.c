#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Aufruf: ./bubblesort Anzahl\n");
        return 1;
    }

    srand((unsigned int) time(NULL));
    int n = atoi(argv[1]);
    int *a = (int*) calloc((size_t) n, sizeof (int));

    if (a == NULL)
    {
        printf("Speicherreservierung fehlgeschlagen!\n");
        return 1;
    }

    printf("Bitte %d ganze Zahlen eingeben: ", n);

    for (int i = 0; i < n; ++i)
    {
        if (scanf("%i", &a[i]) != 1)
        {
            a[i] = rand();
            printf("%d\n", a[i]);
        }
    }

    for (int i = n; i > 1; --i)
    {
        for (int j = 0; j < i - 1; ++j)
        {
            if (a[j] > a[j + 1])
            {
                int tmp = a[j + 1];
                a[j + 1] = a[j];
                a[j] = tmp;
            }
        }
    }

    printf("Sortierte Zahlenfolge: \n");

    for (int i = 0; i < n; ++i)
    {
        printf("%d\n", a[i]);
    }

    free(a);
    return 0;
}
