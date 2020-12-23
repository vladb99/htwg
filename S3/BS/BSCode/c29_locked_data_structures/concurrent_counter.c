#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

double calculateTime(struct timespec *start, struct timespec *end);

int NUM_THREADS = 9;
int TIMES_TO_INCREMENT = 1000000;
int LOOPS = 1000;

typedef struct __counter_t {
    long long int value;
    pthread_mutex_t lock;
} counter_t;

void init(counter_t *c) {
    c->value = 0;
    pthread_mutex_init(&c->lock, NULL);
}

void *increment(void *arg) {
    counter_t *c = (counter_t *) arg;
    pthread_mutex_lock(&c->lock);
    for (int i = 0; i < TIMES_TO_INCREMENT; i++)
    {
        c->value++;
    }
    pthread_mutex_unlock(&c->lock);

    return NULL;
}

int main(int argc, char *argv[]) {
    double avgTimeToCount = 0;
    for (size_t i = 0; i < LOOPS; i++)
    {
        pthread_t threads[NUM_THREADS];
        counter_t counter;
        struct timespec start, end;

        init(&counter);

        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        for (int i = 0; i < NUM_THREADS; i++)
        {
            pthread_create(&threads[i], NULL, increment, &counter);
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