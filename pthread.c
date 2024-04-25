#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 3

// global variables for average, minimum, and maximum values
double avg_value = 0;
int min_value = INT_MAX;
int max_value = INT_MIN;

// function for worker thread that calculates average value
void *calculate_average(void *arg) {
    int *numbers = (int *)arg;
    int i, sum = 0;

    for (i = 0; i < NUM_THREADS; i++) {
        sum += numbers[i];
    }
    avg_value = (double)sum / NUM_THREADS;

    pthread_exit(NULL);
}

// function for worker thread that finds maximum value
void *find_maximum(void *arg) {
    int *numbers = (int *)arg;
    int i;

    for (i = 0; i < NUM_THREADS; i++) {
        if (numbers[i] > max_value) {
            max_value = numbers[i];
        }
    }

    pthread_exit(NULL);
}

// function for worker thread that finds minimum value
void *find_minimum(void *arg) {
    int *numbers = (int *)arg;
    int i;

    for (i = 0; i < NUM_THREADS; i++) {
        if (numbers[i] < min_value) {
            min_value = numbers[i];
        }
    }

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    int i, numbers[NUM_THREADS];
    pthread_t threads[NUM_THREADS];

    // read in list of numbers from command line arguments
    for (i = 1; i <= NUM_THREADS; i++) {
        numbers[i - 1] = atoi(argv[i]);
    }

    // create three worker threads
    pthread_create(&threads[0], NULL, calculate_average, (void *)numbers);
    pthread_create(&threads[1], NULL, find_maximum, (void *)numbers);
    pthread_create(&threads[2], NULL, find_minimum, (void *)numbers);

    // wait for the threads to finish
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // output the results
    printf("The average value is %.2f\n", avg_value);
    printf("The minimum value is %d\n", min_value);
    printf("The maximum value is %d\n", max_value);

    return 0;
}
