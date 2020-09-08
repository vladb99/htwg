/*
* intliteral.c
*
* Beispiel-Programm Zahlen-Literale
*
* Autor: H.Drachenfels
* Erstellt am: 26.10.2018
*/
#include <stdio.h> 
int main(void) {
    printf("%x\n", 12);
    printf("%d\n", 012);
    printf("%o\n", 0x12);
    printf("%u\n", 34U);
    printf("%ld\n", 56L);
    printf("%lld\n", 78LL);

    return 0;
}