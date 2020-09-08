#include <stdio.h>  // printf
#include <stdlib.h> // atoi

int min(int, int);
int max(int, int);
int sum(int, int);

typedef int (*int_function_int_int)(int, int);

int main(int argc, char *argv[])
{
    // int (*f[])(int, int) = {min, max, sum, NULL};
    int_function_int_int f[] = {min, max, sum, NULL};

    if (argc != 3)
    {
        fprintf(stderr, "Aufruf: %s Zahl Zahl\n", argv[0]);
        return 1;
    }

    int m = atoi(argv[1]);
    int n = atoi(argv[2]);

    for (int i = 0; f[i] != NULL; ++i)
    {
        printf("%d\n", f[i](m, n));
    }

    return 0;
}

int min(int a, int b)
{
    return a < b ? a : b;
}

int max(int a, int b)
{
    return a > b ? a : b;
}

int sum(int a, int b)
{
    return a + b;
}