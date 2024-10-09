#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int mails = 0;
pthread_mutex_t mutex;

void *function1() {
    for (int i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&mutex);
        mails++;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main(int argc, const char * argv[]) {
    int i;
    pthread_t threads[3];
    pthread_mutex_init(&mutex, NULL);

    for (i = 0; i < 3; i++) {
        if (pthread_create(&threads[i], NULL, &function1, NULL) != 0) {
            printf("Failed to create thread number %d\n", i);
            return i;
        }
        printf("Thread number %d has been created\n", i);
    }
    for (i = 0; i < 3; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            printf("Failed to join thread number %d\n", i);
            return i;
        }
        printf("Thread number %d has finished execution\n", i);
    }

    pthread_mutex_destroy(&mutex);
    printf("Mails: %d\n", mails);

    return 0;
}
