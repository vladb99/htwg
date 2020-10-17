#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define BILLION  1000000000L;

int main(int argc, char **argv) {
    struct timespec requestStart, requestEnd;
    long long accum;

    if( clock_gettime( CLOCK_REALTIME, &requestStart) == -1 ) {
      perror( "clock gettime" );
      exit( EXIT_FAILURE );
    }

    system( argv[1] );

    if( clock_gettime( CLOCK_REALTIME, &requestEnd) == -1 ) {
      perror( "clock gettime" );
      exit( EXIT_FAILURE );
    }

    accum = ( requestEnd.tv_sec - requestStart.tv_sec )
          + ( requestEnd.tv_nsec - requestStart.tv_nsec )
            / BILLION;
    printf( "%lf\n", accum );

    return 0;
}