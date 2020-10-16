#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int pfd, nbytes;
    char child_string[] = "Hello from child!\n";
    char parent_string[] = "Hello from parent!\n";

    char string_to_read[] = "U receiving me?\n";

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
        //nbytes = read(pfd, readBuffer, sizeof(string_to_read) + 1);
        //printf("CHILD (%d): %s\n", getpid(), readBuffer);

        nbytes = write(pfd, child_string, strlen(child_string));
    }
    else // parent
    {
        //wait(NULL);
        //nbytes = read(pfd, readBuffer, sizeof(string_to_read) + 1);
        //printf("PARENT (%d): %s\n", getpid(), readBuffer);

        nbytes = write(pfd, parent_string, strlen(parent_string));
    }
    nbytes = read(pfd, readBuffer, 80);
    printf("%s\n", readBuffer);
    return 0;
}