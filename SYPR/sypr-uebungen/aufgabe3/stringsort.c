#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void bubblesort(char *list[]);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Aufruf: %s Anzahl\n", *argv);
        return 1;
    }

    srand((unsigned int) time(NULL));
    int n = atoi(argv[1]);

    if (n < 1) {
        printf("Anzahl muss midestens 1 sein");
        return 1;
    }

    char *a[n];

    for (int i = 0; i < 6; ++i) 
    {
        a[i] = (char*) malloc(strlen(argv[1]) * sizeof(char));

        if (a[i] == NULL)
        {
            printf("Speicherreservierung fehlgeschlagen!\n");
            return 1;
        }
    }

    printf("Unsortiertes Feld:");






    free(a); // maybe it needs to be iterative -> all strings must be freed
    return 0;
}

void bubblesort(char *list[])
{

}
