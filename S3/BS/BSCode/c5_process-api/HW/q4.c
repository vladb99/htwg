#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

void run_execl();
void run_execle();
void run_execlp();
void run_execv();
void run_execvp();
void run_execvpe();

// http://openbook.rheinwerk-verlag.de/linux_unix_programmierung/Kap07-009.htm#t2t36

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
        //run_execvp();
        //run_execl();
        //run_execle();
        //run_execlp();
        run_execv();
        //run_execvpe();
    }
    else // parent
    {
        
    }
    return 0;
}

void run_execl()
{
    execl("/bin/ls", "ls", NULL);
}

void run_execle()
{
    char *myargs[3];
    myargs[0] = strdup("/bin/ls");
    myargs[1] = strdup("ls");
    myargs[2] = NULL;
    execle(myargs[0], myargs[1], myargs[2], myargs);
}

void run_execlp()
{
    execlp("/bin/ls", "ls", NULL);
}

void run_execvp()
{
    char *myargs[2];
    myargs[0] = strdup("ls");
    myargs[1] = NULL;
    execvp(myargs[0], myargs);
}

void run_execv()
{
    char *myargs[4];
    myargs[0] = strdup("/bin/ls");
    myargs[1] = strdup("-a");
    myargs[2] = strdup("..");
    myargs[3] = NULL;
    execvp(myargs[0], myargs);
}

void run_execvpe() {
    char *path = getenv("PATH");
    char pathenv[strlen(path) + sizeof("PATH=")];
    char *envp[] = {pathenv, NULL};

    char *myargs[4];
    myargs[0] = strdup("ls");
    myargs[1] = NULL;
    //execvpe(myargs[0], myargs, envp);
}
