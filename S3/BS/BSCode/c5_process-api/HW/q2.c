#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

void both_write();
void both_read();

int main(int argc, char *argv[])
{   
    //both_read();
    both_write();
    return 0;
}

void both_write() {
    int pfd, nbytes;
    char child_string[] = "Hello from child!\n";
    char parent_string[] = "Hello from parent!\n";
    char readBuffer[80];

    pfd = open("question_2.txt", O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);

    int rc = fork();
    if (rc < 0) // fork failed
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0) // child
    {
        nbytes = write(pfd, child_string, strlen(child_string));
    }
    else // parent
    {
        int wc = wait(NULL);
        nbytes = write(pfd, parent_string, strlen(parent_string));
    }
}

void both_read() {
    int pfd, nbytes;
    char string_to_read[] = "U receiving me?";
    char readBuffer[80];

    pfd = open("question_2.txt", O_CREAT | O_RDWR, S_IRWXU);

    int rc = fork();
    if (rc < 0) // fork failed
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0) // child
    {
        nbytes = read(pfd, readBuffer, sizeof(string_to_read));
        lseek(pfd, 0, SEEK_SET);
        printf("CHILD (%d): %s, %d\n", getpid(), readBuffer, nbytes);
    }
    else // parent
    {
        nbytes = read(pfd, readBuffer, sizeof(string_to_read));
        lseek(pfd, 0, SEEK_SET);
        printf("PARENT (%d): %s, %d\n", getpid(), readBuffer, nbytes);
    }
}
