#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sched.h>
#include <time.h>

#define BILLION 1000000000L

struct timespec correctTimer(struct timespec start, struct timespec end);

int main(void) {
    int first_pipefd[2], second_pipefd[2];
    int count = 1000000;
    int overhead = 0;
    int overheadFor = 0;
    struct timespec start, end, temp;
    long long diff = 0;
    long long accum = 0;
    long long overheadAccum = 0;

    // for Overheads
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    for (int i = 0; i < count; i++) {}
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    temp = correctTimer(start, end);
    overheadFor = (BILLION * temp.tv_sec + temp.tv_nsec);

    for (int i = 0; i < count; i++) {
        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);
        temp = correctTimer(start, end);
        overheadAccum += (BILLION * temp.tv_sec + temp.tv_nsec);
    }
    overhead = overheadAccum / count;
    printf("Average Overhead of CLOCK_MONOTONIC_RAW: %i in nano seconds\n", overhead);

    // Set processor to run process on, child inherits the mask
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(0, &mask);
    if (sched_setaffinity(0, sizeof(mask), &mask) == -1) {
        exit(EXIT_FAILURE);
    }

    if (pipe(first_pipefd) == -1) {
        fprintf(stderr, "pipe init\n");
        exit(EXIT_FAILURE);
    }
    if (pipe(second_pipefd) == -1) {
        fprintf(stderr, "pipe init\n");
        exit(EXIT_FAILURE);
    }

    pid_t cpid = fork();

    if (cpid == -1) {
        fprintf(stderr, "fork\n");
        exit(EXIT_FAILURE);
    } else if (cpid == 0) {
        for (int i = 0; i < count; i++) {
            read(first_pipefd[0], NULL, 0);
            write(second_pipefd[1], NULL, 0);
        }
    } else {
        for (int i = 0; i < count; i++) {
            write(first_pipefd[1], NULL, 0);
            clock_gettime(CLOCK_MONOTONIC_RAW, &start);
            read(second_pipefd[0], NULL, 0);
            clock_gettime( CLOCK_MONOTONIC_RAW, &end);
            temp = correctTimer(start, end);
            diff = (BILLION * temp.tv_sec + temp.tv_nsec) / 2;
            accum += diff;
        }

        printf("Context switch time = %lli nanoseconds with overhead\n", accum / count);
        printf("Context switch time = %lli nanoseconds without overhead\n", (accum - overhead * count - overheadFor) / count);
    }
    return 0;
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
