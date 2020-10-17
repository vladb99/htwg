#include <stdio.h>	/* for printf */
#include <stdint.h>	/* for uint64 definition */
#include <stdlib.h>	/* for exit() definition */
#include <time.h>	/* for clock_gettime */

#define BILLION 1000000000L

int localpid(void) {
	static int a[9] = { 0 };
	return a[0];
}

main(int argc, char **argv)
{
	long long diff;
	struct timespec start, end;
	int i;

	/* measure monotonic time */
	clock_gettime(CLOCK_MONOTONIC, &start);	/* mark start time */
	sleep(1);	/* do stuff */
	clock_gettime(CLOCK_MONOTONIC, &end);	/* mark the end time */

	diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
	printf("elapsed time = %lli nanoseconds\n", (long long int) diff);

	/* now re-do this and measure CPU time */
	/* the time spent sleeping will not count (but there is a bit of overhead */
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);	/* mark start time */
	sleep(1);	/* do stuff */
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);		/* mark the end time */

	diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
	printf("elapsed process CPU time = %lli nanoseconds\n", (long long int) diff);

    /* measure real time */
	clock_gettime(CLOCK_REALTIME, &start);	/* mark start time */
	sleep(1);	/* do stuff */
	clock_gettime(CLOCK_REALTIME, &end);	/* mark the end time */

	diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
	printf("elapsed time = %lli nanoseconds\n", (long long int) diff);

	return 0;
}