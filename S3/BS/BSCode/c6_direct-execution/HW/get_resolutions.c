#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(void) {
    struct timespec res;

    if (clock_getres(CLOCK_REALTIME, &res) == -1 ) {
        perror( "CLOCK_REALTIME get resolution" );
        return EXIT_FAILURE;
    }
    printf("Resolution of CLOCK_REALTIME is %ld nano seconds.\n", res.tv_nsec);

    if (clock_getres(CLOCK_MONOTONIC, &res) == -1 ) {
        perror( "CLOCK_MONOTONIC get resolution" );
        return EXIT_FAILURE;
    }
    printf("Resolution of CLOCK_MONOTONIC is %ld nano seconds.\n", res.tv_nsec);

    if (clock_getres(CLOCK_MONOTONIC_RAW, &res) == -1 ) {
        perror( "CLOCK_MONOTONIC_RAW get resolution" );
        return EXIT_FAILURE;
    }
    printf("Resolution CLOCK_MONOTONIC_RAW is %ld nano seconds.\n", res.tv_nsec);

    if (clock_getres(CLOCK_PROCESS_CPUTIME_ID, &res) == -1 ) {
        perror( "CLOCK_PROCESS_CPUTIME_ID get resolution" );
        return EXIT_FAILURE;
    }
    printf("Resolution CLOCK_PROCESS_CPUTIME_ID is %ld nano seconds.\n", res.tv_nsec);
}
