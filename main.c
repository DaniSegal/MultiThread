#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


void *function1() {
    printf("Thread 1 is working\n");
    return NULL;
}

int main(int argc, const char * argv[]) {
    pthread_t thread1;
    pthread_create(&thread1, NULL, &function1, NULL);
    pthread_join(thread1, NULL);
    printf("Hello, World!\n");
    return 0;
}
