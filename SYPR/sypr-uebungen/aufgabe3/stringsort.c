#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void bubblesort(int size, char *list[]);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Aufruf: %s Anzahl\n", *argv);
        return 1;
    }

    srand((unsigned int) time(NULL));
    int n = atoi(argv[1]);
    int m = strlen(argv[1]) + 1;

    if (n < 1)
    {
        printf("Anzahl muss mindestens 1 sein\n");
        return 1;
    }

    char **arrayString = (char**) malloc(n * sizeof (char*));
    if (arrayString == NULL)
    {
        printf("Speicherallokierungsfehler\n");
        return 1;
    }

    printf("Unsortiertes Feld:\n");
    for (int i = 0; i < n; ++i)
    {
        int r = rand() % n;

        arrayString[i] = (char*) malloc(m * sizeof (char));
        if (arrayString[i] == NULL)
        {
            printf("Speicherallokierungsfehler\n");
            for (int j = 0; j < i; ++j)
            {
                free(arrayString[j]);
            }
            free(arrayString);
            return 1;
        }

        sprintf(arrayString[i], "%d", r);
        printf("%s ", arrayString[i]);
    }

    //bubblesort(n, arrayString);

    printf("\nSortiertes Feld:\n");
    char *sb = (char*) malloc(n * m * sizeof(char));
    if (sb == NULL)
    {
        printf("Speicherallokierungsfehler\n");
        return 1;
    }
    strcpy(sb, arrayString[0]);
    for (int i = 1; i < n; ++i)
    {
        if (strcmp(arrayString[i], arrayString[i - 1]) == 0)
        {
            strcat(sb, "*");
        }
        else
        {
            strcat(sb, " ");
            strcat(sb, arrayString[i]);
        }
    }

    printf("%s\n", sb);

    for (int i = 0; i < n; ++i)
    {
        free(arrayString[i]);
    }

    free(sb);
    free(arrayString);
    return 0;
}

void bubblesort(int size, char *list[])
{
    for (int i = size; i > 1; --i)
    {
        for (int j = 0; j < i - 1; ++j)
        {
            if (strcmp(list[j], list[j + 1]) > 0)
            {
                char *tmp = list[j + 1];
                list[j + 1] = list[j];
                list[j] = tmp;
            }
        }
    }
}

