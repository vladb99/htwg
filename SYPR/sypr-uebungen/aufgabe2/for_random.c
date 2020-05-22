#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Aufruf: ./for_random Anzahl\n");
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

    for (int i = 0; i < n; ++i)
    {
        int r = rand() % n;
        a[r] = r;
    }

    free(a);
    return 0;
}
