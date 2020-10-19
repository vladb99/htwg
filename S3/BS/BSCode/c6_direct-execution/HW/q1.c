#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define BILLION 1000000000L

struct timespec correctTimer(struct timespec start, struct timespec end);

int main(void) {
    struct timespec requestStart, requestEnd;
    long long accum;
    char buf;
    char readbuffer[80];
    int count = 1000000;//2 000 000;

    //for (int i = 0; i < count; i++) {
    //    clock_gettime( CLOCK_MONOTONIC, &requestStart);
    //    read(0, NULL, 0);
     //   clock_gettime( CLOCK_MONOTONIC, &requestEnd);
     //   accum += BILLION * (requestEnd.tv_sec - requestStart.tv_sec)
     //       + requestEnd.tv_nsec - requestStart.tv_nsec;
    //}
    //accum /= count;

    clock_gettime( CLOCK_MONOTONIC, &requestStart);

    for (int i = 0; i < count; i++) {
        read(0, NULL, 0);
    }

    clock_gettime( CLOCK_MONOTONIC, &requestEnd);

    printf("start tv_sec %li\n", requestStart.tv_sec);
    printf("start tv_nsec %li\n", requestStart.tv_nsec);

    printf("end tv_sec %li\n", requestEnd.tv_sec);
    printf("end tv_nsec %li\n", requestEnd.tv_nsec);

    struct timespec correctedTimer = correctTimer(requestStart, requestEnd);

    accum = (BILLION * correctedTimer.tv_sec + correctedTimer.tv_nsec) / (count);
    //accum = (BILLION * (requestEnd.tv_sec - requestStart.tv_sec)
    //        + requestEnd.tv_nsec - requestStart.tv_nsec);
    
    printf( "%lli\n",(long long int) accum );
    return 0;
}

struct timespec correctTimer(struct timespec start, struct timespec end)
{
    struct timespec temp;

    if ((end.tv_nsec-start.tv_nsec)<0)
    {
            temp.tv_sec = end.tv_sec - start.tv_sec - 1;
            temp.tv_nsec = 1000000000 + end.tv_nsec - start.tv_nsec;
    }
    else 
    {
            temp.tv_sec = end.tv_sec - start.tv_sec;
            temp.tv_nsec = end.tv_nsec - start.tv_nsec;
    }
    return temp;
}