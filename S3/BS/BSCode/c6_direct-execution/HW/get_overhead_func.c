#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define BILLION 1000000000L

struct timespec correctTimer(struct timespec start, struct timespec end);

int main(void) {
    struct timespec start, end, temp;
    int count = 10000000;
    long long accum = 0;

    // Erste immer ein bisschen langsam
    //clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    //clock_gettime(CLOCK_MONOTONIC_RAW, &end);

    for (int i = 0; i < count; i++) {
        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);
        temp = correctTimer(start, end);
        accum += (BILLION * temp.tv_sec + temp.tv_nsec);
    }
    printf("Average Overhead of CLOCK_MONOTONIC_RAW %lli\n", accum / count);

    for (int i = 0; i < count; i++) {
        clock_gettime(CLOCK_MONOTONIC, &start);
        clock_gettime(CLOCK_MONOTONIC, &end);
        temp = correctTimer(start, end);
        accum += (BILLION * temp.tv_sec + temp.tv_nsec);
    }
    printf("Average Overhead of CLOCK_MONOTONIC %lli\n", accum / count);

    for (int i = 0; i < count; i++) {
        clock_gettime(CLOCK_REALTIME, &start);
        clock_gettime(CLOCK_REALTIME, &end);
        temp = correctTimer(start, end);
        accum += (BILLION * temp.tv_sec + temp.tv_nsec);
    }
    printf("Average Overhead of CLOCK_REALTIME %lli\n", accum / count);

    for (int i = 0; i < count; i++) {
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
        temp = correctTimer(start, end);
        accum += (BILLION * temp.tv_sec + temp.tv_nsec);
    }
    printf("Average Overhead of CLOCK_PROCESS_CPUTIME_ID %lli\n", accum / count);
}

struct timespec correctTimer(struct timespec start, struct timespec end)
{
    struct timespec temp;

    if ((end.tv_nsec-start.tv_nsec)<0)
    {
            temp.tv_sec = end.tv_sec - start.tv_sec - 1;
            temp.tv_nsec = 1000000000 + end.tv_nsec - start.tv_nsec;
    }
    else 
    {
            temp.tv_sec = end.tv_sec - start.tv_sec;
            temp.tv_nsec = end.tv_nsec - start.tv_nsec;
    }
    return temp;
}