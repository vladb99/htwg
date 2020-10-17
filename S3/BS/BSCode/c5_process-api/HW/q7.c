#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int nbytes;
    int parent_pid = getpid();
    int rc = fork();
    if (rc < 0) {
        // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) { // child
        close(STDOUT_FILENO);
        nbytes = printf("%s\n", "CHILD");
        //fprintf(stderr, "%d %s\n", nbytes, strerror(errno));
        open("./q7.output", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
        nbytes = fflush(stdout);
    } else { // parent
        int wc = wait(NULL);
        printf("PARENT\n");
    }
    return 0;
}