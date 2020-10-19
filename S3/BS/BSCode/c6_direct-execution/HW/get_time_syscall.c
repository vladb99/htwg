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
    int overhead = 0;
    long long diff = 0;
    long long accum = 0;

    for (int i = 0; i < count; i++) {
        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);
        temp = correctTimer(start, end);
        accum += (BILLION * temp.tv_sec + temp.tv_nsec);
    }
    overhead = accum / count;
    printf("Average Overhead of CLOCK_MONOTONIC_RAW %i\n", overhead);

    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    for (int i = 0; i < count; i++) {
        read(0, NULL, 0);
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    temp = correctTimer(start, end);
    diff = (BILLION * temp.tv_sec + temp.tv_nsec);

    printf("Time cost without overheard of systemcall with CLOCK_MONOTONIC_RAW in nano seconds %lli\n", diff / count);
    printf("Time cost of systemcall with CLOCK_MONOTONIC_RAW in nano seconds %lli\n\n\n", (diff / count) - overhead);

    accum = 0;

    for (int i = 0; i < count; i++) {
        clock_gettime(CLOCK_MONOTONIC, &start);
        clock_gettime(CLOCK_MONOTONIC, &end);
        temp = correctTimer(start, end);
        accum += (BILLION * temp.tv_sec + temp.tv_nsec);
    }
    overhead = accum / count;
    printf("Average Overhead of CLOCK_MONOTONIC %i\n", overhead);

    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < count; i++) {
        read(0, NULL, 0);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    temp = correctTimer(start, end);
    diff = (BILLION * temp.tv_sec + temp.tv_nsec);

    printf("Time cost without overheard of systemcall with CLOCK_MONOTONIC in nano seconds %lli\n", diff / count);
    printf("Time cost of systemcall with CLOCK_MONOTONIC in nano seconds %lli\n", (diff / count) - overhead);

    accum = 0;
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