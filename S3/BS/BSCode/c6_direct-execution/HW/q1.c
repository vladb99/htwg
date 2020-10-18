#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define BILLION 1000000000L

int main(void) {
    struct timespec requestStart, requestEnd;
    long long accum;
    char buf;
    char readbuffer[80];
    int count = 1100000;//2 000 000;

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

    accum = (BILLION * (requestEnd.tv_sec - requestStart.tv_sec)
            + requestEnd.tv_nsec - requestStart.tv_nsec) / count;
    //accum = (BILLION * (requestEnd.tv_sec - requestStart.tv_sec)
    //        + requestEnd.tv_nsec - requestStart.tv_nsec);
    
    printf( "%lli\n",(long long int) accum );
    return 0;
}