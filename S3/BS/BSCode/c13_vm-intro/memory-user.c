#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double calculateTime();

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "usage: ./memory-user <memory> <time>");
        exit(1);
    }

    int memory = atoi(argv[1]) * 1024 * 1024;
    int time = atoi(argv[2]);
    int length = (int)(memory / sizeof(int));

    int *array = malloc(length * sizeof(int));
    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC_RAW, &start);

    while (1)
    {
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);
        double diff = calculateTime(&start, &end);
        
        if (diff > time) {
            break;
        }

        for (int i = 0; i < length; i++) {
            array[i] += 1; 
        }
    }
}

double calculateTime(struct timespec *start, struct timespec *end) {
    if (end->tv_nsec < start->tv_nsec) {
        return (end->tv_sec - start->tv_sec - 1) * 1000 +
            (1000000000 + end->tv_nsec - start->tv_nsec) / 1000000;
    }
    return (end->tv_sec - start->tv_sec) * 1000 +
            (end->tv_nsec - start->tv_nsec) / 1000000;
}