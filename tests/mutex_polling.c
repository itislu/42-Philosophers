#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>

#define SLEEP_TIME 1

void *lock_mutex_master(void *mutex) {
    pthread_mutex_lock((pthread_mutex_t *)mutex);
	sleep(SLEEP_TIME);
    pthread_mutex_unlock((pthread_mutex_t *)mutex);
    return NULL;
}

void *lock_mutex(void *mutex) {
    pthread_mutex_lock((pthread_mutex_t *)mutex);
    pthread_mutex_unlock((pthread_mutex_t *)mutex);
    return NULL;
}

void *sleep_thread(void *arg) {
    sleep(SLEEP_TIME);
    return NULL;
}

void test_threads(int num_threads) {
    pthread_t threads[num_threads];
    pthread_mutex_t mutex;
	struct timeval start, end;

    pthread_mutex_init(&mutex, NULL);

	gettimeofday(&start, NULL);

    // Test threads locking and unlocking a mutex
	pthread_create(&threads[0], NULL, lock_mutex_master, &mutex);
    for (int i = 1; i < num_threads; i++) {
        pthread_create(&threads[i], NULL, lock_mutex, &mutex);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

	gettimeofday(&end, NULL);
	printf("Time taken mutex: %ld\n", (end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec);

	gettimeofday(&start, NULL);

    // Test threads sleeping
    for (int i = 0; i < num_threads; i++) {
        pthread_create(&threads[i], NULL, sleep_thread, NULL);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

	gettimeofday(&end, NULL);
	printf("Time taken sleep: %ld\n", (end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec);

    pthread_mutex_destroy(&mutex);
}


void test_threads_opposite(int num_threads) {
    pthread_t threads[num_threads];
    pthread_mutex_t mutex;
	struct timeval start, end;

    pthread_mutex_init(&mutex, NULL);

	gettimeofday(&start, NULL);

    // Test threads sleeping
    for (int i = 0; i < num_threads; i++) {
        pthread_create(&threads[i], NULL, sleep_thread, NULL);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

	gettimeofday(&end, NULL);
	printf("Time taken sleep: %ld\n", (end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec);

	gettimeofday(&start, NULL);

    // Test threads locking and unlocking a mutex
	pthread_create(&threads[0], NULL, lock_mutex_master, &mutex);
    for (int i = 1; i < num_threads; i++) {
        pthread_create(&threads[i], NULL, lock_mutex, &mutex);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

	gettimeofday(&end, NULL);
	printf("Time taken mutex: %ld\n", (end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec);

    pthread_mutex_destroy(&mutex);
}

int	main(int argc, char **argv)
{
	int num_threads = atoi(argv[1]);

	test_threads(num_threads);
	test_threads_opposite(num_threads);
	return (0);
}