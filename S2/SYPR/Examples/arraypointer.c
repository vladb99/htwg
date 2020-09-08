#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

int main(void)
{
    const int n = 4;
    int *a = (int*) calloc((size_t) n, sizeof(int));
    if(a == NULL)
    {
        printf("Speicherreservierung fehlgeschlagen!\n");
        return 1;
    }

    a[0] = 3421;
    a[1] = 3442;
    a[2] = 3635;
    a[3] = 3814;

    printf("&a = %p\n", (void*) &a);
    printf("a = %p\n", (void*) a);

    for (int i = 0; i < n; ++i) 
    {
        printf("%d :%p %d\n", i, (void*) &a[i], a[i]);
    }

    printf("sizeof a = %zu\n", sizeof a); /* pointer size */
    printf("%d * sizeof *a = %zu\n", n, n * sizeof *a);

    free(a);
    return 0;
}