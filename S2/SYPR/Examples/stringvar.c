#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char a[] = "hallo";
    const char *s = "halli";
    char *t = NULL;

    //printf("%d", strcmp(a, s)); // ASCII difference

    if (strcmp(a, s) < 0)
    {
        t = (char*) malloc(sizeof a + strlen(s));
        if (t == NULL)
        {
            fprintf(stderr, "Kein Heap-Speicher mehr\n");
            return 1;
        }

        strcat(strcpy(t, a), s);
    }
    else
    {
        t = (char*) calloc(1, sizeof (char));
        if (t == NULL)
        {
            fprintf(stderr, "Kein Heap-Speicher mehr\n");
            return 1;
        }
    }

    printf("a = %p %s\ns = %p %s\nt = %p %s\n",
           (void*) a, a, (void*) s, s, (void*) t, t);

    printf("sizeof a = %zu\n", sizeof a);
    printf("sizeof s = %zu\n", sizeof s);
    printf("sizeof t = %zu\n", sizeof t);

    printf("strlen(a) = %zu\n", strlen(a));
    printf("strlen(s) = %zu\n", strlen(s));
    printf("strlen(t) = %zu\n", strlen(t));
    
    s = a;

    free(t);
    
    return 0;
}