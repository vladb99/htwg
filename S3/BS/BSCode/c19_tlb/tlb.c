#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

double calculateTime();

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
    int array[numPages * pageSize / sizeof(int)];

    printf("Page size: %d Byte\n", pageSize);
    printf("int size: %lu Byte\n", sizeof(int));

    int jump = pageSize / sizeof(int);
    printf("jump: %d\n", jump);

    for (int j = 0; j < trials; j++) {
        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        for (int i = 0; i < numPages * jump; i += jump) {
            array[i] += 1;
        }
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);
        timeSum += calculateTime(&start, &end);
    }
    double averagePageAccess = timeSum / trials / numPages;
    printf("Average page access: %f ns\n", averagePageAccess);
}

double calculateTime(struct timespec *start, struct timespec *end) {
    if (end->tv_nsec < start->tv_nsec) {
        return (end->tv_sec - start->tv_sec - 1) * 1000000000 +
            (1000000000 + end->tv_nsec - start->tv_nsec);
    }
    return (end->tv_sec - start->tv_sec) * 1000000000 +
            (end->tv_nsec - start->tv_nsec);
}
