#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

#define NUM_THREADS 200

typedef struct {
    pthread_mutex_t mutex;
    int count;
} Barrier;

void custom_barrier_wait(Barrier* barrier) {
    pthread_mutex_lock(&barrier->mutex);
    barrier->count++;
    pthread_mutex_unlock(&barrier->mutex);

    while (barrier->count < NUM_THREADS) {
        usleep(100);  // Sleep for a short time to avoid busy waiting
    }
}

void* myThreadFun(void* vargp) {
    Barrier* barrier = (Barrier*)vargp;

    printf("Thread waiting at barrier\n");
    custom_barrier_wait(barrier);
	// usleep(1000);
    printf("Thread proceeding\n");

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    Barrier barrier;

    memset(&barrier, 0, sizeof(barrier));
    pthread_mutex_init(&barrier.mutex, NULL);

    // Create the threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, myThreadFun, &barrier);
		printf("Thread %d has started\n", i);
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&barrier.mutex);

    return 0;
}