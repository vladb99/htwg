#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sched.h>
#include <time.h>

#define BILLION 1000000000L

struct timespec correctTimer(struct timespec start, struct timespec end);

int main(void) {
    int first_pipefd[2], second_pipefd[2];
    int count = 10000000;
    int overhead = 0;
    struct timespec start, end, temp;
    long long diff = 0;
    long long accum = 0;
    long long overheadAccum = 0;

    struct timespec startUsage, endUsage, tempUsage;
    struct rusage usage;

    for (int i = 0; i < count; i++) {
        clock_gettime(CLOCK_MONOTONIC, &start);
        clock_gettime(CLOCK_MONOTONIC, &end);
        temp = correctTimer(start, end);
        overheadAccum += (BILLION * temp.tv_sec + temp.tv_nsec);
    }
    overhead = overheadAccum / count;
    printf("Average Overhead of CLOCK_MONOTONIC: %i in nano seconds\n", overhead);

    // Set processor to run process on, child inherits the mask
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(0, &mask);
    int result = sched_setaffinity(0, sizeof(mask), &mask);

    if (result == -1) {
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
        clock_gettime(CLOCK_MONOTONIC, &startUsage);

        for (int i = 0; i < count; i++) {
            write(first_pipefd[1], NULL, 0);
            clock_gettime(CLOCK_MONOTONIC, &start);
            read(second_pipefd[0], NULL, 0);
            clock_gettime(CLOCK_MONOTONIC, &end);
            temp = correctTimer(start, end);
            diff = (BILLION * temp.tv_sec + temp.tv_nsec) / 2;
            accum += diff;
        }

        clock_gettime(CLOCK_MONOTONIC, &endUsage);
        int success = getrusage(RUSAGE_SELF, &usage);

        if (success == -1) {
            exit(EXIT_FAILURE);
        }

        long long utime = BILLION * usage.ru_utime.tv_sec + 1000 * usage.ru_utime.tv_usec;
        long long stime = BILLION * usage.ru_stime.tv_sec + 1000 * usage.ru_stime.tv_usec;

        tempUsage = correctTimer(startUsage, endUsage);
        long long timeNS = BILLION * tempUsage.tv_sec + tempUsage.tv_nsec;

        printf("CPU usage during clock: %lli\n", (utime + stime)/timeNS*100);

        printf("Context switch time = %lli nanoseconds with overhead\n", accum / count);
        printf("Context switch time = %lli nanoseconds without overhead\n", (accum - overhead * count) / count);
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
