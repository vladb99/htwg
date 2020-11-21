#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

double calculateTime();

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "usage: ./tlb.c numberOfPages numberOfTrials");
        exit(1);
    }
    
    struct timespec start, end;
    
    double timeSum = 0;

    int numberOfPages = atoi(argv[1]);
    int numberOfTrials = atoi(argv[2]);
    int pagesize = getpagesize();
    int array[numberOfPages * pagesize / sizeof(int)];
    int jump = pagesize / sizeof(int);

    printf("Pagesize: %d\n", pagesize);
    printf("sizeof(int): %lu\n", sizeof(int));
    printf("jump: %d\n", jump);

    clock_gettime(CLOCK_MONOTONIC_RAW, &start);

    for (int j = 0; j < numberOfTrials; j++) {
        
        for (int i = 0; i < numberOfPages * jump; i += jump){
            array[i] += 1;
        }
        
        //timeSum += calculateTime(&start, &end);
    }
    
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);

    //double averagePageAccess = timeSum / numberOfPages / numberOfTrials;

    int nloops = numberOfPages * numberOfTrials;

    //printf("page acces: %f nanosec.\n", averagePageAccess);

    printf("Average page access: %f ns\n", calculateTime(&start, &end) / nloops);
    //printf("page access: %f nanosec.\n", calculateTime(&start, &end) / nloops);

    //valgrind --leak-check=yes ./tlb
    //gcc -o tlb tlb.c -g
    //gdb tlb
    //run 500 1000000
    //gcc -o tlb tlb.c -Wall -Wextra -Wpedantic
}

double calculateTime(struct timespec *start, struct timespec *end) {
    if (end->tv_nsec < start->tv_nsec) {
        return (end->tv_sec - start->tv_sec - 1) * 1000000000 + (1000000000 + end->tv_nsec - start->tv_nsec);
    }
    return (end->tv_sec - start->tv_sec) * 1000000000 + (end->tv_nsec - start->tv_nsec);
}