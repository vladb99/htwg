#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int parse_output(void);
bool startsWith(char *pre, char *str);

#define BUFSIZE 128

int main(void) {
    parse_output();
}

int parse_output(void) {
    char *cmd = malloc(BUFSIZE * sizeof(char));
    //char *cmd = "./lottery.py -l 100:100,100:100 -c";   
    char *cmp = "-->";
    char *buf2 = malloc(BUFSIZE * sizeof(char));

    char buf[BUFSIZE];
    FILE *fp;

    close(STDOUT_FILENO);
    open("data-job-length.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);

    for (int i = 1; i <= 1000; i+=1) {
        sprintf(cmd, "./lottery.py -l %d:100,%d:100 -s 10 -c", i, i); 
        if ((fp = popen(cmd, "r")) == NULL) {
            printf("Error opening pipe!\n");
            return -1;
        }

        while (fgets(buf2, BUFSIZE, fp) != NULL) {
            if (startsWith(cmp, buf2)) {
                int count = 0;
                char* token = strtok(buf2, " ");
                while (token != NULL) {
                    if (count == 6) {
                        printf( "%d ", atoi(token));
                    }
                    token = strtok(NULL, " ");
                    count++;
                }
            }
        }
        printf("%d\n", i);
    }
    if(pclose(fp))  {
        printf("Command not found or exited with error status\n");
        return -1;
    }

    return 0;
}

bool startsWith(char *pre, char *str)
{
    size_t lenpre = strlen(pre),
           lenstr = strlen(str);
    return lenstr < lenpre ? false : memcmp(pre, str, lenpre) == 0;
}