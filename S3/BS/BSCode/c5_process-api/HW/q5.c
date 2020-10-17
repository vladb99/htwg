#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void wait_in_parent();
void wait_in_child();
// What does wait() return?
// -> Wenn erfolgreich, es gibt die Prozess ID zurück. Wenn Error dann -1

// What happens if you use wait() in the child?
// -> Wenn wait im child, gibt wait -1 zurück. Child can't wait for parent. Use atexit() for that

int main(int argc, char *argv[]) {
    wait_in_parent();
    return 0;
}

void wait_in_parent() {
    int rc = fork();
    if (rc < 0) {
        // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) { // child
        printf("CHILD %d\n", getpid());
    } else { // parent
        int wc = wait(NULL);
        printf("PARENT %d\n", getpid());
        printf("%d\n", wc);
    }
}

void wait_in_child() {
    int rc = fork();
    if (rc < 0) {
        // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) { // child
        int wc = wait(NULL);
        printf("CHILD\n");
        printf("%d\n", wc);
    } else { // parent
        printf("PARENT\n");
    }
}