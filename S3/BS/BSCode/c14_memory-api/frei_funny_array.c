#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int *array = (int*) malloc(100 * sizeof(int));
    free(&array[50]);
    return 0;
}