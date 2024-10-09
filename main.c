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
    pthread_t thread1, thread2;
    pthread_mutex_init(&mutex, NULL);

    if (pthread_create(&thread1, NULL, &function1, NULL) != 0) {
        printf("Failed to create the first thread\n");
        return 1;
    }
    if (pthread_create(&thread2, NULL, &function1, NULL) != 0) {
        printf("Failed to create the second thread\n");
        return 2;
    }
    if (pthread_join(thread1, NULL) != 0) {
        printf("Failed to join the first thread\n");
        return 1;
    }
    if (pthread_join(thread2, NULL) != 0) {
        printf("Failed to join the second thread\n");
        return 2;
    }
    pthread_mutex_destroy(&mutex);
    printf("Mails: %d\n", mails);

    return 0;
}
