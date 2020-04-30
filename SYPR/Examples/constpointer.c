#include <stdio.h>

int main(void) {
    const int i = 0;
    const int *p = &i;

    int j = 0;
    int * const q = &j;

    // Fehler, *p konstant: *p = 0;
    p = NULL;

    // Fehler, q konstant: q = NULL;
    *q = 0;

    return 0;
}