#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>

#define NUMCPUS 2

double calculateTime(struct timespec *start, struct timespec *end);

int NUM_THREADS = 8;
int TIMES_TO_INCREMENT = 1000000;
int LOOPS = 100000;
int THRESHOLD = 64;

typedef struct __counter_t {
    int global; // global count
    pthread_mutex_t glock; // global lock
    int local[NUMCPUS]; // per-CPU count
    pthread_mutex_t llock[NUMCPUS]; // ... and locks
    int threshold; // update frequency
} counter_t;

// init: record threshold, init locks, init values
// of all local counts and global count
void init(counter_t *c, int threshold) {
    c->threshold = threshold;
    c->global = 0;
    pthread_mutex_init(&c->glock, NULL);
    int i;
    for (i = 0; i < NUMCPUS; i++) {
        c->local[i] = 0;
        pthread_mutex_init(&c->llock[i], NULL);
    }
}

// update: usually, just grab local lock and update
// local amount; once local count has risen ’threshold’,
// grab global lock and transfer local values to it
void *update(void *arg) {
    counter_t *c = (counter_t *) arg;
    pid_t threadID = syscall(__NR_gettid);
    int cpu = threadID % NUMCPUS;
    pthread_mutex_lock(&c->llock[cpu]);
    c->local[cpu] += 1;
    if (c->local[cpu] >= c->threshold) {
        // transfer to global (assumes amt>0)
        pthread_mutex_lock(&c->glock);
        c->global += c->local[cpu];
        pthread_mutex_unlock(&c->glock);
        c->local[cpu] = 0;
    }
    pthread_mutex_unlock(&c->llock[cpu]);
    return NULL;
}

int main(int argc, char *argv[]) {
    double avgTimeToCount = 0;
    for (size_t i = 0; i < LOOPS; i++)
    {
        pthread_t threads[NUM_THREADS];
        counter_t counter;
        struct timespec start, end;

        init(&counter, THRESHOLD);

        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        for (int i = 0; i < NUM_THREADS; i++)
        {
            pthread_create(&threads[i], NULL, update, &counter);
        }

        for (int i = 0; i < NUM_THREADS; i++)
        {
            pthread_join(threads[i], NULL);
        }
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);

        double timeToCount = calculateTime(&start, &end);
        avgTimeToCount += timeToCount;
    }

    printf("Time taken to count: %f ns\n", avgTimeToCount / LOOPS);
    return 0;
}

double calculateTime(struct timespec *start, struct timespec *end) {
    if (end->tv_nsec < start->tv_nsec) {
        return (end->tv_sec - start->tv_sec - 1) * 1000000000 +
            (1000000000 + end->tv_nsec - start->tv_nsec);
    }
    return (end->tv_sec - start->tv_sec) * 1000000000 +
            (end->tv_nsec - start->tv_nsec);
}