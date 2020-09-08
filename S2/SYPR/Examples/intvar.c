#include <stdio.h>

int main(void) {
    int i = 0;
    int j = 1;

    printf("i = %d\n", i);
    printf("j = %d\n", j);

    printf("&i = %p\n", (void*) &i);
    printf("&j = %p\n", (void*) &j);

    printf("sizeof (int) = %zu\n", sizeof (int));
    printf("sizeof i = %zu\n", sizeof i);

}