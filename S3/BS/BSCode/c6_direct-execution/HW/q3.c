#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/types.h>
  #include <sys/wait.h>
#include <sched.h>
#include <time.h>

#define BILLION 1000000000L

struct timespec correctTimer(struct timespec start, struct timespec end);

// Same as q2.c, but this time the child sends the end time via pipe

int main(int argc, char *argv[]) {
    // measure context switch
    int first_pipefd[2], second_pipefd[2], time_pipefd[2];
    int anzLoops = 5;//1000000;
    struct timespec start, end;
    long long diff;

    cpu_set_t mask;
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
    if (pipe(time_pipefd) == -1) {
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
        // Child sends the time via pipe
        clock_gettime(CLOCK_MONOTONIC, &end);
        int n = sizeof(struct timespec);
        if (write(time_pipefd[1], &end, n) != n) {
            fprintf(stderr, "child: Failed to write in time pipe\n");
                exit(EXIT_FAILURE);
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

        int n = sizeof(struct timespec);
        if (read(time_pipefd[0], &end, n) != n) {
            fprintf(stderr, "parent: Failed to read from pipe\n");
                exit(EXIT_FAILURE);
        }
        wait(NULL);

        struct timespec correctedTimer = correctTimer(start, end);

        diff = (BILLION * correctedTimer.tv_sec + correctedTimer.tv_nsec) / (anzLoops * 2);
        printf("Context switch time = %lli nanoseconds\n", (long long int) diff);
    }
    return 0;
}

struct timespec correctTimer(struct timespec start, struct timespec end)
{
    struct timespec temp;

    if ((end.tv_nsec - start.tv_nsec ) < 0)
    {
            temp.tv_sec = end.tv_sec - start.tv_sec - 1;
            temp.tv_nsec = BILLION + end.tv_nsec - start.tv_nsec;
    }
    else 
    {
            temp.tv_sec = end.tv_sec - start.tv_sec;
            temp.tv_nsec = end.tv_nsec - start.tv_nsec;
    }
    return temp;
}