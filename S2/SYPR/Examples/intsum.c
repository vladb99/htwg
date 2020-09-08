#include <stdio.h>

int main(void) {
    int sum = 0;

    printf("Ganze Zahlen eingeben (Ende mit STRG-D):\n");

    int number;
    while(scanf("%d", &number) > 0) {
        sum += number;
    }

    printf("Summe: %d\n", sum);

    return 0;
}