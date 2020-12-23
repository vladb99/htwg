#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>

#define BUCKETS (101)

double calculateTime(struct timespec *start, struct timespec *end);

int NUM_THREADS = 4;
int UPDATES = 50000;
int LOOPS = 1000;

// basic node structure
typedef struct __node_t {
    int key;
    struct __node_t *next;
} node_t;

// basic list structure (one used per list)
typedef struct __list_t {
    node_t *head;
    pthread_mutex_t lock;
} list_t;

typedef struct __hash_t {
    list_t lists[BUCKETS];
} hash_t;

void List_Init(list_t *L) {
    L->head = NULL;
    pthread_mutex_init(&L->lock, NULL);
}

void List_Insert(list_t *L, int key) {
    // synchronization not needed
    node_t *new = malloc(sizeof(node_t));
    if (new == NULL) {
        perror("malloc");
        return;
    }
    new->key = key;

    // just lock critical section
    pthread_mutex_lock(&L->lock);
    new->next = L->head;
    L->head = new;
    pthread_mutex_unlock(&L->lock);
}

int List_Lookup(list_t *L, int key) {
    int rv = -1;
    pthread_mutex_lock(&L->lock);
    node_t *curr = L->head;
    while (curr) {
        if (curr->key == key) {
            rv = 0;
            break;
        }
    curr = curr->next;
    }
    pthread_mutex_unlock(&L->lock);
    return rv; // now both success and failure
}

void Hash_Init(hash_t *H) {
    int i;
    for (i = 0; i < BUCKETS; i++) {
        List_Init(&H->lists[i]);
    }
}

void Hash_Insert(hash_t *H, int key) {
    List_Insert(&H->lists[key % BUCKETS], key);
}

int Hash_Lookup(hash_t *H, int key) {
    return List_Lookup(&H->lists[key % BUCKETS], key);
}

void *update(void *arg) {
    hash_t *map = (hash_t*) arg;
    for (int key = 0; key < UPDATES; key++)
    {
        Hash_Insert(map, key);
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    hash_t map;
    Hash_Init(&map);

    double avgTimeToUpdate = 0;
    for (size_t i = 0; i < LOOPS; i++)
    {
        pthread_t threads[NUM_THREADS];
        struct timespec start, end;

        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        for (int i = 0; i < NUM_THREADS; i++)
        {
            pthread_create(&threads[i], NULL, update, &map);
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
