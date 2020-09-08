#include <stdio.h>

int max(int a, int b);

int main(void)
{
    {
        int value = max(7, 8);
        printf("max(7, 8) = %d\n", value);
    }

    {
        int (*maximum)(int, int) = max;
        int value = maximum(7, 8);
        printf("max(7, 8) = %d\n", value);
    }

    return 0;
}

int max(int a, int b)
{
    if (a > b) return a;
    return b;
}