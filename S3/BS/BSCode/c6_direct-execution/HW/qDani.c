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
    int first_pipefd[2];
    int second_pipefd[2];
    long long diff;

    int anzahlLoops = 100000;

    //Nur eine CPU verwenden
    cpu_set_t  mask;
    CPU_ZERO(&mask);
    CPU_SET(0, &mask);

    struct timespec start, end;

    //Error handling pipe1
    if (pipe(first_pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    //Error handling pipe2
    if (pipe(second_pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    //Create Child Prozess
    pid_t cpid = fork();

    if (cpid == -1) { //Error handling fork
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (cpid == 0) {    // child

	//Nur eine CPU verwenden
	int result = sched_setaffinity(0, sizeof(mask), &mask);
        
	//Error handling eine CPU verwenden
	if (result == -1) {
            exit(EXIT_FAILURE);
        }

        for (size_t i = 0; i < anzahlLoops; i++) {
            read(first_pipefd[0], NULL, 0);
            write(second_pipefd[1], NULL, 0);
        }
    } else {           // parent

	//Nur eine CPU verwenden
        int result = sched_setaffinity(0, sizeof(mask), &mask);

        //Error handling eine CPU verwenden
        if (result == -1) {
            exit(EXIT_FAILURE);
        }	

	clock_gettime(CLOCK_MONOTONIC, &start);

        for (size_t i = 0; i < anzahlLoops; i++) {
            write(first_pipefd[1], NULL, 0);
            read(second_pipefd[0], NULL, 0);
        }
	clock_gettime(CLOCK_MONOTONIC, &end);

	diff = (BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec) / anzahlLoops;
        printf("Context switch time = %lli nanoseconds\n", (long long int) diff);
    }
    return 0;
}
