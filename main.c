#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define EXIT_FAILURE 1
// Global variable to hold the wanted number of threads
#define NUM_THREADS 7

pthread_mutex_t mutex;

// Structure to hold thread arguments
typedef struct {
    int *mailBoxes;
    int mailBoxesNum;
    int threadNum;
} thread_args_t;

void *function1(void *args) {
    thread_args_t *threadArgs = (thread_args_t *)args;
    int *mailBoxes = threadArgs->mailBoxes;
    int mailBoxesNum = threadArgs->mailBoxesNum;
    int threadNum = threadArgs->threadNum;

    for (int i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&mutex);
        mailBoxes[threadNum % mailBoxesNum]++;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main(int argc, const char * argv[]) {
    int i;
    pthread_t threads[NUM_THREADS];
    thread_args_t threadArgs[NUM_THREADS];

    // Initialize the mutex
    if ((pthread_mutex_init(&mutex, NULL)) != 0) {
        perror("Failed to initialize mutex");
        return EXIT_FAILURE;
    }


    srand(time(NULL));
    int mailBoxesNum = (rand() % NUM_THREADS) + 1;
    int *mailBoxes = malloc(mailBoxesNum * sizeof(int));
    if (!mailBoxes) {
        perror("Failed to allocate memory for mailBoxes");
        return EXIT_FAILURE;
    }
    // Initialize mailBoxes to 0
    for (i = 0; i < mailBoxesNum; i++) {
        mailBoxes[i] = 0;
    }
    //  initialize thread arguments
    
    for (i = 0; i < NUM_THREADS; i++) {
        threadArgs[i].mailBoxes = mailBoxes;
        threadArgs[i].mailBoxesNum = mailBoxesNum;
        threadArgs[i].threadNum = i;
    }

    // Create threads
    for (i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, function1, (void *)&threadArgs[i]) != 0) {
            fprintf(stderr, "Failed to create thread number %d\n", i);
            perror(NULL);
            return i;
        }
        printf("Thread number %d has been created\n", i);
    }
    // Join threads
    for (i = 0; i < NUM_THREADS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            fprintf(stderr, "Failed to join thread number %d\n", i);
            perror(NULL);
            return i;
        }
        printf("Thread number %d has finished execution\n", i);
    }

    pthread_mutex_destroy(&mutex);

    // Print the mailBoxes contents
    for (i = 0; i < mailBoxesNum; i++) {
        printf("Mailbox %d: %d\n", i, mailBoxes[i]);
    }

    free(mailBoxes);

    return 0;
}
