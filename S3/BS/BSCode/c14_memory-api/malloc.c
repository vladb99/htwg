#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int *p = (int*) malloc(sizeof(int));
    *p = 10;
    printf("%d", *p);
}
