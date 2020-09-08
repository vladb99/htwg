#include <stdio.h>
#include <stdlib.h>

struct raum
{
    int zimmer;
    const char *art;
    char gebaeude;
};

int main(int argc, char *argv[])
{
    if (argc == 1) 
    {
        return 1;
    }
    int sum = 0;
    for (int i = 1; i < argc; ++i) 
    {
        int n = atoi(argv[i]);
        sum += n;
    }
    printf("%d", sum);
}
