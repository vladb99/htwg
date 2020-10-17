#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

void child_A_writes();
void child_B_writes();
int global_fd[2];

int main(int argc, char *argv[]) {
    child_A_writes();
    //child_B_writes();
    return 0;
}

void child_A_writes() {
    int fd[2], nbytes;
    int parent_pid = getpid();
    char readbuffer[80];
    char buf;

    pipe(fd);
    int child_a = fork();

    if (child_a < 0) { // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (child_a == 0) { // child a
        printf("%s\n", "CHILD_A\n");
        dup2(fd[1], STDOUT_FILENO);
        // setvbuf(stdout,NULL,_IONBF,0); unbuffered
        close(fd[0]);
        char str[] = "Hallo Geschwister B. Ich bin A!";
        //write(fd[1], str, strlen(str));
        printf("%s", str);
        close(fd[1]);
    } else { // parent
        int wc = wait(NULL);
        printf("%s\n", "PARENT\n");
        int child_b = fork();

        if (child_b < 0) {
            fprintf(stderr, "fork failed\n");
            exit(1);
        } else if (child_b == 0) { // child b
            printf("%s", "CHILD_B\n");
            dup2(fd[0], STDIN_FILENO);
            close(fd[1]);
            while (read(STDIN_FILENO, &buf, 1) > 0) {
                printf("%c", buf);
            }
            write(STDOUT_FILENO, "\n", 1);
            close(fd[0]);
        }
    }
}

void sig_handler(int signum) {
    printf("%s\n", "CHILD_A\n");
    close(global_fd[1]);
    char buf;
    while (read(global_fd[0], &buf, 1) > 0) {
        write(STDOUT_FILENO, &buf, 1);
    }
    write(STDOUT_FILENO, "\n", 1);
    close(global_fd[0]);
    exit(0);
}

void child_B_writes() {
    int nbytes;
    int parent_pid = getpid();
    char readbuffer[80];
    char buf;

    pipe(global_fd);
    int child_a = fork();

    if (child_a < 0) { // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (child_a == 0) { // child a
        signal(SIGCONT, sig_handler);
        pause();

    } else { // parent
        printf("%s\n", "PARENT\n");
        int child_b = fork();

        if (child_b < 0) {
            fprintf(stderr, "fork failed\n");
            exit(1);
        } else if (child_b == 0) { // child b
            printf("%s\n", "CHILD_B\n");
            close(global_fd[0]);
            char str[] = "Hallo Geschwister A. Ich bin B!";
            write(global_fd[1], str, strlen(str));
            close(global_fd[1]);
            kill(child_a, SIGCONT);
            exit(0);
        }
    }
}
