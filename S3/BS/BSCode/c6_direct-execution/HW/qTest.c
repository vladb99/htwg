#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    long int ST;
    long int ET;
    int i;
    int a[1000];
    int b[1000];
    

    struct timespec gettime_now;
    clock_gettime(CLOCK_REALTIME, &gettime_now);
    ST = gettime_now.tv_nsec;
    for (i = 0; i < 1000; i++) {
        a[i] = b[i];
    }
    clock_gettime(CLOCK_REALTIME, &gettime_now);
    ET = gettime_now.tv_nsec;
    printf("Time diff: %ld\n", ET - ST);
}