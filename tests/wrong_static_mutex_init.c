#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define THREAD_NUM 8

pthread_mutex_t mutex[2];
int fuel = 50;
int water = 10;

void* routine(void* args) {
	pthread_mutex_lock(&mutex[0]);
	pthread_mutex_lock(&mutex[1]);

    fuel += 50;
    water = fuel;
    printf("Incremented fuel to: %d set water to %d\n", fuel, water);
    pthread_mutex_unlock(&mutex[0]);
    pthread_mutex_unlock(&mutex[1]);
}

int main(int argc, char *argv[]) {
    pthread_t th[THREAD_NUM];
	for (int i = 0; i < 2; i++) {
		mutex[i] = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	}
    // pthread_mutex_init(&mutexFuel, NULL);
    // pthread_mutex_init(&mutexWater, NULL);
    int i;
    for (i = 0; i < THREAD_NUM; i++) {
        if (pthread_create(&th[i], NULL, &routine, NULL) != 0) {
            perror("Failed to create thread");
        }
    }

    for (i = 0; i < THREAD_NUM; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to join thread");
        }
    }
    printf("Fuel: %d\n", fuel);
    printf("Water: %d\n", water);
    for (int i = 0; i < 2; i++) {
		pthread_mutex_destroy(&mutex[i]);
	}
    return 0;
}