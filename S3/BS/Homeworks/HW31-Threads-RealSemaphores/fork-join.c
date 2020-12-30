#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "common_threads.h"

/*
* Solves the fork/join problem.
* Uses the Linux way to work with semaphores.
* It also implements semaphores by only using locks and condition variables.
* On Linux compile with: gcc -o fork-join fork-join.c -pthread
*/

typedef struct __Zem_t {
    int value;
    pthread_cond_t cond;
    pthread_mutex_t lock;
} Zem_t;

// only one thread can call this
void Zem_init(Zem_t *s, int value) {
    s->value = value;
    Cond_init(&s->cond);
    Mutex_init(&s->lock);
}

void Zem_wait(Zem_t *s) {
    Mutex_lock(&s->lock);
    while (s->value <= 0) {
        Cond_wait(&s->cond, &s->lock);
    }
    s->value--;
    Mutex_unlock(&s->lock);
}

void Zem_post(Zem_t *s) {
    Mutex_lock(&s->lock);
    s->value++;
    Cond_signal(&s->cond);
    Mutex_unlock(&s->lock);
}

//sem_t s;
Zem_t s;

void *child(void *arg) {
    usleep(1000000);
    printf("child\n");
    // use semaphore here
    //Sem_post(&s);
    Zem_post(&s);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p;
    printf("parent: begin\n");
    // init semaphore here
    //Sem_init(&s, 0);
    Zem_init(&s, 0);
    Pthread_create(&p, NULL, child, NULL);
    // use semaphore here
    //Sem_wait(&s);
    Zem_wait(&s);
    printf("parent: end\n");
    return 0;
}
