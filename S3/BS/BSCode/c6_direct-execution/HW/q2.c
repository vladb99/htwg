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

// Program to measure the cost of a context switch.

int main(int argc, char *argv[]) {
    int first_pipefd[2], second_pipefd[2];
    int anzLoops = 1000000;
    struct timespec start, end;
    long long diff;

    //cpu_set_t mask;
    int mask;
    CPU_ZERO(&mask);
    CPU_SET(0, &mask);
    int result = sched_setaffinity(0, sizeof(mask), &mask);

    if (pipe(first_pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    if (pipe(second_pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t cpid = fork();

    if (cpid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (cpid == 0) { // child
        if (result == -1) {
            exit(EXIT_FAILURE);
        }

        for (size_t i = 0; i < anzLoops; i++) {
            read(first_pipefd[0], NULL, 0);
            write(second_pipefd[1], NULL, 0);
        }
    } else { // parent
        if (result == -1) {
            exit(EXIT_FAILURE);
        }

        clock_gettime(CLOCK_MONOTONIC, &start);
        for (size_t i = 0; i < anzLoops; i++) {
            write(first_pipefd[1], NULL, 0);
            read(second_pipefd[0], NULL, 0);
        }
        clock_gettime( CLOCK_MONOTONIC, &end);

        struct timespec correctedTimer = correctTimer(start, end);

        diff = (BILLION * correctedTimer.tv_sec + correctedTimer.tv_nsec) / (anzLoops * 2);
        printf("Context switch time = %lli nanoseconds\n", (long long int) diff);
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
