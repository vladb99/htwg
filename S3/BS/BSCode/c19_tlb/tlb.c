#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sched.h>
#include <fcntl.h>

double calculateTime();

// gdb tbl -> run 10 1000
// valgrind --leak-check=yes ./tlb 10 1000
// gcc -o tlb tlb.c -Wall -Wextra -Wpedantic

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "usage: ./tlb <num-pages> <trials>");
        exit(1);
    }

    double timeSum = 0;
    int numPages = atoi(argv[1]);
    int trials = atoi(argv[2]);
    int pageSize = getpagesize();

    struct timespec start, end;
    int *array = (int *)malloc(numPages * pageSize);

    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(0, &mask);
    if (sched_setaffinity(0, sizeof(mask), &mask) == -1) {
        exit(EXIT_FAILURE);
    }

    //printf("Page size: %d Byte\n", pageSize);
    printf("int size: %lu Byte\n", sizeof(int));

    int jump = pageSize / sizeof(int);
    printf("jump: %d\n", jump);

    // Overhead timer
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    double overheadTimer = calculateTime(&start, &end);
    printf("Overhead timer: %f\n", overheadTimer);

    // Overhead for loop
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    for (int j = 0; j < trials; j++) {
        for (int i = 0; i < numPages * jump; i += jump) {}
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    double overheadLoop = calculateTime(&start, &end);
    printf("Overhead loop: %f\n", overheadLoop);

    // Page access loop
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    for (int j = 0; j < trials; j++) {
        //clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        for (int i = 0; i < numPages * jump; i += jump) {
            array[i] += 1;
        }
        //clock_gettime(CLOCK_MONOTONIC_RAW, &end);
        //timeSum += calculateTime(&start, &end);
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);

    //timeSum = timeSum - overheadTimer - overheadLoop;
    //double averagePageAccess = timeSum / trials / numPages;
    double averagePageAccess = (calculateTime(&start, &end)) / trials / numPages;
    printf("Average page access: %f ns\n", averagePageAccess);
    free(array);
}

double calculateTime(struct timespec *start, struct timespec *end) {
    if (end->tv_nsec < start->tv_nsec) {
        return (end->tv_sec - start->tv_sec - 1) * 1000000000 +
            (1000000000 + end->tv_nsec - start->tv_nsec);
    }
    return (end->tv_sec - start->tv_sec) * 1000000000 +
            (end->tv_nsec - start->tv_nsec);
}
