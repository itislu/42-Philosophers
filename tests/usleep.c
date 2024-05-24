#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#include <math.h>

#define NUM_THREADS 10
#define NUM_TESTS 5000
#define SLEEP_TIME_US 1000  // Sleep time in microseconds
#define BUFFER_TIME_US 60   // Time buffer for busy-waiting
#define WARMUP_TESTS 1000  // Tests to run before measuring

typedef struct {
    long* diffs;
    int size;
} ThreadResult;

void precise_usleep(long sleep_time_us) {
    struct timeval start, end;
    long elapsed_time_us;
    const long buffer_time_us = BUFFER_TIME_US;  // Time buffer for busy-waiting

    // Get the current time
    if (buffer_time_us > 0) {
        gettimeofday(&start, NULL);
    }

    // Sleep for the bulk of the time
    if (sleep_time_us > buffer_time_us) {
        usleep(sleep_time_us - buffer_time_us);
    }

    // Busy-wait until the full sleep time has passed
    if (buffer_time_us > 0) {
        do {
            gettimeofday(&end, NULL);
            elapsed_time_us = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
        } while (elapsed_time_us < sleep_time_us);
    }
}

void* test_usleep(void* arg) {
    ThreadResult* result = malloc(sizeof(ThreadResult));
    result->diffs = malloc(NUM_TESTS * sizeof(long));
    result->size = NUM_TESTS;
    int thread_id = *((int*)arg);
    free(arg);

    char filename[50];
    sprintf(filename, "thread_%d.txt", thread_id);
    FILE* file = fopen(filename, "w");

    for (int i = 0; i < WARMUP_TESTS; i++) {
        struct timeval start, end;

        gettimeofday(&start, NULL);
        precise_usleep(SLEEP_TIME_US);
        gettimeofday(&end, NULL);
    }

    for (int i = 0; i < NUM_TESTS; i++) {
        struct timeval start, end;

        gettimeofday(&start, NULL);
        precise_usleep(SLEEP_TIME_US);
        gettimeofday(&end, NULL);

        long start_time_us = start.tv_sec * 1000000 + start.tv_usec;
        long end_time_us = end.tv_sec * 1000000 + end.tv_usec;
        long actual_sleep_time_us = end_time_us - start_time_us;

        result->diffs[i] = labs(actual_sleep_time_us - SLEEP_TIME_US);
        fprintf(file, "%ld\n", result->diffs[i]);
    }

    fclose(file);
    return result;
}

int compare_long(const void* a, const void* b) {
    return (*(long*)a - *(long*)b);
}

int main() {
    pthread_t threads[NUM_THREADS];
    long* diffs = malloc(NUM_THREADS * NUM_TESTS * sizeof(long));

    for (int i = 0; i < NUM_THREADS; i++) {
        int* thread_id = malloc(sizeof(int));
        *thread_id = i;
        pthread_create(&threads[i], NULL, test_usleep, thread_id);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        void* ret;
        pthread_join(threads[i], &ret);
        ThreadResult* result = (ThreadResult*)ret;
        for (int j = 0; j < NUM_TESTS; j++) {
            diffs[i * NUM_TESTS + j] = result->diffs[j];
        }
        free(result->diffs);
        free(result);
    }

    qsort(diffs, NUM_THREADS * NUM_TESTS, sizeof(long), compare_long);

    long min_diff = diffs[0];
    long max_diff = diffs[NUM_THREADS * NUM_TESTS - 1];

    long sum = 0;
    for (int i = 0; i < NUM_THREADS * NUM_TESTS; i++) {
        sum += diffs[i];
    }
    double mean = (double)sum / (NUM_THREADS * NUM_TESTS);
    double median = (double)(diffs[(NUM_THREADS * NUM_TESTS) / 2] + diffs[(NUM_THREADS * NUM_TESTS - 1) / 2]) / 2;

    double sum_sq_diff = 0;
    for (int i = 0; i < NUM_THREADS * NUM_TESTS; i++) {
        sum_sq_diff += (diffs[i] - mean) * (diffs[i] - mean);
    }
    double stddev = sqrt(sum_sq_diff / (NUM_THREADS * NUM_TESTS));

    printf("Overall Mean difference: %.2f us\n", mean);
    printf("Overall Median difference: %.2f us\n", median);
    printf("Overall Standard deviation: %.2f us\n", stddev);
    printf("Overall Minimum difference: %ld us\n", min_diff);
    printf("Overall Maximum difference: %ld us\n", max_diff);

    FILE* file = fopen("overall_diffs.txt", "w");
    for (int i = 0; i < NUM_THREADS * NUM_TESTS; i++) {
        fprintf(file, "%ld\n", diffs[i]);
    }
    fclose(file);

    free(diffs);

    return 0;
}
