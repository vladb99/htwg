#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int matrix[2][3] = {{10,11,12},{20,21,22}};

    printf("&matrix = %p\n", (void*) &matrix);
    printf("matrix = %p\n", (void*) matrix);

    for(int i = 0; i < 2; ++i)
    {
        printf("[%d] %p\n", i, (void*) matrix[i]);

        for (int j = 0; j < 3; ++j)
        {
            printf("  [%d] %p: %d\n", j, (void*) &matrix[i][j], matrix[i][j]);
        }
    }

    return 0;
}