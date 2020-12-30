#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "common_threads.h"

//
// Here, you have to write (almost) ALL the code. Oh no!
// How can you show that a thread does not starve
// when attempting to acquire this mutex you build?
//

typedef struct __ns_mutex_t {
    int room1;          // how many waiting threads in room1
    int room2;          // how many waiting threads in room2
    sem_t mutex;        // helps to protect the counters
    sem_t turnstile1;
    sem_t turnstile2;
} ns_mutex_t;

void ns_mutex_init(ns_mutex_t *m) {
    m->room1 = 0;
    m->room2 = 0;
    Sem_init(&m->mutex, 1);
    Sem_init(&m->turnstile1, 1);
    Sem_init(&m->turnstile2, 0);    // set to 0 because threads can only acquire it, when all threads have left room1
}

void ns_mutex_acquire(ns_mutex_t *m) {
    Sem_wait(&m->mutex);
    m->room1 += 1;  // transition in room1
    Sem_post(&m->mutex);

    usleep(1000); // force first thread to wait for others to join room1

    Sem_wait(&m->turnstile1);
    m->room2 += 1;  // transition in room2
    Sem_wait(&m->mutex); // acquire lock, in order to decremt room1
    m->room1 -= 1;  // leave room1

    if (m->room1 == 0) { // last thread coming from room1
        Sem_post(&m->mutex); // release the lock
        Sem_post(&m->turnstile2); // open the barrier to room2; IMPORTANT turnstile1 is still locked. This prevents threads that come later to join the rooms.
    } else { // if ther are still threads coming from room1
        Sem_post(&m->mutex); // release the lock
        Sem_post(&m->turnstile1); // open the barrier, so more thread can come from room1
    }

    Sem_wait(&m->turnstile2);   // wait here, if last thread didn't open this barrier
    m->room2 -= 1;  // decrement the number of threads in room2. These threads now go into the critical section
    
    // force a sleep before critical section, to show that when other threads arrive, it is too late.
    // They must now wait for this patch of threads to finish.
    usleep(10);
    // Following critical section..
}

void ns_mutex_release(ns_mutex_t *m) {
    if (m->room2 == 0) {
        Sem_post(&m->turnstile1);
    } else {
        Sem_post(&m->turnstile2);
    }
}

ns_mutex_t m;
int value = 0;
int num_threads = 0;

typedef struct __tinfo_t {
    int thread_id;
} tinfo_t;

void *worker(void *arg) {
    tinfo_t *t = (tinfo_t *) arg;
    printf("thread %d: arrived\n", t->thread_id);

    ns_mutex_acquire(&m);
    value++;
    ns_mutex_release(&m);

    printf("thread %d: ended\n", t->thread_id);
    return NULL;
}

int main(int argc, char *argv[]) {
    assert(argc == 2);
    num_threads = atoi(argv[1]);
    assert(num_threads > 0);

    pthread_t p[num_threads];
    tinfo_t t[num_threads];

    printf("begin\n");
    ns_mutex_init(&m);

    int i;
    for (i = 0; i < num_threads; i++) {
	    t[i].thread_id = i;
        // if number of threads reaches half of all threads,
        // force a sleep, in order to see if the first half gets executed all
        // before the second half
        if (i == num_threads / 2) {
            usleep(2000);
        }
	    Pthread_create(&p[i], NULL, worker, &t[i]);
    }

    for (i = 0; i < num_threads; i++) {
        Pthread_join(p[i], NULL);
    }

    printf("end: value %d\n", value);
    return 0;
}
