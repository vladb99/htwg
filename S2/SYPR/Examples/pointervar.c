#include <stdio.h>

int main(void) {
    int i = 3082;
    int *p = &i;

    printf("p = %p\n", (void*) p);
    printf("&p = %p\n", (void*) &p);
    printf("sizeof p = %zu\n", sizeof p);
    printf("*p = %d\n", *p);

    return 0;
}