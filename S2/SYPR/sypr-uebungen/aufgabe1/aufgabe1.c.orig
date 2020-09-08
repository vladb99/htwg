#include <stdio.h>
#include <stdbool.h>

int main(void) {

    int numI = 115;
    short int numSI = 115;
    long int numLI = 115L;
    long long int numLLI = 115LL;
    unsigned int numUI = 0xffffffffU;
    unsigned short int numUSI = 0xffffU;
    unsigned long int numULI = 0xfffffffffUL;
    unsigned long long int numULLI = 0xfffffffffULL;

    float numF = 3.14F;
    double numD = 3.14;
    long double numLD = 3.14L;

    char sign = 'c';
    signed char byteSC = -1;
    unsigned char byteUC = 0xff;

    bool boolean = 1;

    char* s = (char*) "Hallo";

    printf("Adresse: %p, Platzbedarf: %zu, Typ: %s, Name: %s, Wert: %d\n", (void*) &numI, sizeof(numI), "int", "numI", numI);
    printf("Adresse: %p, Platzbedarf: %zu, Typ: %s, Name: %s, Wert: %hd\n", (void*) &numSI, sizeof(numSI), "short int", "numSI", numSI);
    printf("Adresse: %p, Platzbedarf: %zu, Typ: %s, Name: %s, Wert: %ld\n", (void*) &numLI, sizeof(numLI), "long int", "numLI", numLI);
    printf("Adresse: %p, Platzbedarf: %zu, Typ: %s, Name: %s, Wert: %lld\n", (void*) &numLLI, sizeof(numLLI), "long long int", "numLLI", numLLI);
    printf("Adresse: %p, Platzbedarf: %zu, Typ: %s, Name: %s, Wert: %u\n", (void*) &numUI, sizeof(numUI), "unsigned int", "numUI", numUI);
    printf("Adresse: %p, Platzbedarf: %zu, Typ: %s, Name: %s, Wert: %hu\n", (void*) &numUSI, sizeof(numUSI), "unsigned short int", "numUSI", numUSI);
    printf("Adresse: %p, Platzbedarf: %zu, Typ: %s, Name: %s, Wert: %lu\n", (void*) &numULI, sizeof(numULI), "unsigned long int", "numULI", numULI);
    printf("Adresse: %p, Platzbedarf: %zu, Typ: %s, Name: %s, Wert: %llu\n", (void*) &numULLI, sizeof(numULLI), "unsigned long long int", "numULLI", numULLI);
    printf("Adresse: %p, Platzbedarf: %zu, Typ: %s, Name: %s, Wert: %f\n", (void*) &numF, sizeof(numF), "float", "numF", numF);
    printf("Adresse: %p, Platzbedarf: %zu, Typ: %s, Name: %s, Wert: %lg\n", (void*) &numD, sizeof(numD), "double", "numD", numD);
    printf("Adresse: %p, Platzbedarf: %zu, Typ: %s, Name: %s, Wert: %Lg\n", (void*) &numLD, sizeof(numLD), "long double", "numLD", numLD);
    printf("Adresse: %p, Platzbedarf: %zu, Typ: %s, Name: %s, Wert: %c\n", (void*) &sign, sizeof(sign), "char", "sign", sign);
    printf("Adresse: %p, Platzbedarf: %zu, Typ: %s, Name: %s, Wert: %d\n", (void*) &byteSC, sizeof(byteSC), "signed char", "byteSC", byteSC);
    printf("Adresse: %p, Platzbedarf: %zu, Typ: %s, Name: %s, Wert: %u\n", (void*) &byteUC, sizeof(byteUC), "unsigned char", "byteUC", byteUC);
    printf("Adresse: %p, Platzbedarf: %zu, Typ: %s, Name: %s, Wert: %d\n", (void*) &boolean, sizeof(boolean), "boolean", "boolean", boolean);
    printf("Adresse: %p, Platzbedarf: %zu, Typ: %s, Name: %s, Wert: %s\n", (void*) &s, sizeof(s), "char*", "s", s);

    if (sizeof(int) == 4 && sizeof(long int) == 4 && sizeof(char*) == 4) {
        printf("%s\n", "ILP32");
    } else if(sizeof(int) == 4 && sizeof(long int) == 8 && sizeof(char*) == 8) {
        printf("%s\n", "LP64");
    } else if(sizeof(int) == 4 && sizeof(long int) == 4 && sizeof(long long int) == 8 &&sizeof(char*) == 8) {
        printf("%s\n", "LLP64");
    } else {
        printf("%s\n", "Anderes");
    }

    return 0;
}
