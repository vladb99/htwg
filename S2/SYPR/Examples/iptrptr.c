#include <stdio.h>

int main(void) {
    int i = 0;
    int *p = &i;
    int **pp = &p;

    printf("\n");
    printf("%d\n", *p);
    printf("%d\n", **pp);
    printf("%d\n", *&i);
    printf("%d\n", *&*p);

    return 0;
}