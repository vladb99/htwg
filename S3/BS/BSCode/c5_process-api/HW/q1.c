#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//  1. What value is the variable in the child process? 100
//  2. What happens to the variable when both the child and parent change the value of x?
//      -> Both change the variable from 100 to newvalue

int main(int argc, char *argv[]) {
    printf("hello world (pid:%d)\n", (int) getpid());
    int x = 100;
    int rc = fork();
    if (rc < 0) {
        // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        printf("hello, I am child (pid:%d)\n", (int) getpid());
        printf("value of x before is %d\n", x);
        x = 50;
        printf("value of x after is %d\n", x);
    } else {
        // parent goes down this path (main)
        printf("hello, I am parent of %d (pid:%d)\n", rc, (int) getpid());
        printf("value of x before is %d\n", x);
        x = 25;
        printf("value of x after is %d\n", x);
    }
    printf("value of x is %d\n", x);
    return 0;
}