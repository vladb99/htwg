#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

// https://github.com/ahmedbilal/OSTEP-Solution/blob/master/Chapter%205/question3-yorwos.c

// You should try to ensure that the child process always prints first; can you do this without calling wait() in the parent?
//  ->Ja, indem man den Elternprozess pausiert und wenn es ein SIGCONT Signal kommt, macht er mit dem handler weiter. Das Kindprozess schickt dann dieses Signal nach dem printen.

void sig_handler(int signum) {
    printf("goodbye\n");
    exit(0);
}

int main(int argc, char *argv[])
{   
    int parent_pid = getpid();
    int rc = fork();
    if (rc < 0) // fork failed
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0) // child
    {
        printf("hello\n");
        kill(parent_pid, SIGCONT);
        exit(0);
    }
    else // parent
    {
        signal(SIGCONT, sig_handler);
        pause();
    }
    return 0;
}