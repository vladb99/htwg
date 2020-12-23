#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>

double calculateTime(struct timespec *start, struct timespec *end);

int NUM_THREADS = 4;
int UPDATES = 10000;
int LOOPS = 1000;

// basic node structure
typedef struct __node_t {
    int key;
    struct __node_t *next;
    pthread_mutex_t lock;
} node_t;

// basic list structure (one used per list)
typedef struct __list_t {
    node_t *head;
    pthread_mutex_t lock;
} list_t;

void List_Init(list_t *L) {
    L->head = NULL;
    pthread_mutex_init(&L->lock, NULL);
}

void *update(void *arg) {
    list_t *L = (list_t*) arg;
    for (int key = 0; key < UPDATES; key++)
    {
        node_t *new = malloc(sizeof(node_t));
        if (new == NULL) {
            perror("malloc");
            return NULL;
        }
        new->key = key;
        pthread_mutex_init(&new->lock, NULL);
        node_t *curr = L->head;
        node_t *tmp;

        if (!curr) {
            pthread_mutex_lock(&L->lock);
            curr->next = new;
            pthread_mutex_unlock(&L->lock);
        } else {
            pthread_mutex_lock(&curr->lock);
            while (curr) {
                tmp = curr;
                curr = curr->next;
                pthread_mutex_lock(&curr->lock);
                pthread_mutex_unlock(&tmp->lock);
            }
            curr->next = new;
            pthread_mutex_unlock(&curr->lock);
        }
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    list_t list;
    List_Init(&list);

    double avgTimeToUpdate = 0;
    for (size_t i = 0; i < LOOPS; i++)
    {
        pthread_t threads[NUM_THREADS];
        struct timespec start, end;

        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        for (int i = 0; i < NUM_THREADS; i++)
        {
            pthread_create(&threads[i], NULL, update, &list);
        }

        for (int i = 0; i < NUM_THREADS; i++)
        {
            pthread_join(threads[i], NULL);
        }
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);

        double timeToCount = calculateTime(&start, &end);
        avgTimeToUpdate += timeToCount;
    }

    printf("Time taken to update per thread: %f ns\n", avgTimeToUpdate / LOOPS / NUM_THREADS);
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