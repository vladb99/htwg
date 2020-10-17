#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int parent_pid = getpid();
    int rc = fork();
    if (rc < 0) {
        // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) { // child
        int wc = waitpid(parent_pid, NULL, WUNTRACED);
        printf("CHILD\n");
        printf("%d\n", wc);
    } else { // parent
        printf("PARENT\n");
    }
    return 0;
}