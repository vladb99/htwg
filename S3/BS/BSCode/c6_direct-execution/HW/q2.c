#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sched.h>
#include <time.h>

#define BILLION 1000000000L

int main(int argc, char *argv[]) {
    // measure context switch
    int first_pipefd[2], second_pipefd[2];
    int anzLoops = 1000000;
    struct timespec start, end;

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
        printf("context switch: %f microseconds\n", 
        (float) (BILLION * (end.tv_sec - start.tv_sec)
            + end.tv_nsec - start.tv_nsec) / anzLoops);
    }
    return 0;
}
