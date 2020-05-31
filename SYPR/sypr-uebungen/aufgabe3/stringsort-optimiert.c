#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void bubblesort(void *ptr, size_t count, size_t size, int (*cmp)(const char*, const char*));

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

    if (n < 1) {
        printf("Anzahl muss mindestens 1 sein\n");
        return 1;
    }

    char *arrayString = (char*) malloc(n * m * sizeof (char));
    if (arrayString == NULL)
    {
        printf("Speicherallokierungsfehler\n");
        return 1;
    }

    printf("Unsortiertes Feld:\n");
    for (int i = 0; i < n; ++i)
    {
        int r = rand() % n;
        sprintf(arrayString + i * m, "%d", r);
        printf("%s", arrayString + i * m);
        printf(" ");
    }
    printf("\n");
    
    bubblesort(arrayString, n, m, strcmp);
    
    printf("\nSortiertes Feld:\n");
    char *sb = (char*) malloc(n * m * sizeof(char));
    if (sb == NULL)
    {
        printf("Speicherallokierungsfehler\n");
        return 1;
    }
    strcpy(sb, arrayString);
    for (int i = 1; i < n; ++i)
    {
        if (strcmp(arrayString + i * m, arrayString + (i - 1) * m) == 0)
        {
           strcat(sb, "*");
        }
        else
        {
            strcat(sb, " ");
            strcat(sb, arrayString + i * m);
        }
    }

    printf("%s\n", sb);

    free(sb);
    free(arrayString);
    return 0;
}

void bubblesort(void *ptr, size_t count, size_t size, int (*cmp)(const char*, const char*))
{
    char* tmp = malloc(size);
    for (int i = count; i > 1; --i) {
        for (int j = 0; j < i - 1; ++j)
        {
            char *lhs = ((char*) ptr) + j * size;
            char *rhs = ((char*) ptr) + (j + 1) * size;

            if (cmp(lhs, rhs) > 0) {
                memcpy(tmp, rhs, size);
                memcpy(rhs, lhs, size);
                memcpy(lhs, tmp, size);
            }
        }
    }
    free(tmp);
}
