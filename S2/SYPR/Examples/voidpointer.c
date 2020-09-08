#include <stdio.h>

int main(void) {
    float n = 1;
    void *vp = &n;
    int *ip = (int*) vp;

    printf("%x\n", *ip);
    
    return 0;
} 