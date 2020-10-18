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
    int count = 1000000;
    int a[count];
    int b[count];
    
    printf("%zu\n", sizeof(time_t));
    printf("%zu\n", sizeof(long int));

    struct timespec gettime_now;
    clock_gettime(CLOCK_REALTIME, &gettime_now);
    ST = gettime_now.tv_nsec;
    for (i = 0; i < count; i++) {
        a[i] = b[i];
    }
    clock_gettime(CLOCK_REALTIME, &gettime_now);
    ET = gettime_now.tv_nsec;
    printf("Time diff: %ld\n", ET - ST);
}