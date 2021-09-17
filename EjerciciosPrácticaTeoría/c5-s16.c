#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define SIZE 5
int nums[SIZE] = {0,1,2,3,4};

void * mihilo(void *data) {
    int j = data;
    nums[j] = 2*j;
    printf("Num[i]: %d", nums[j]);
}

int main() {
    int i;
    pid_t pid;
    pthread_t hilo[SIZE];

    for (i = 0; i < SIZE; i++) {
        pthread_create(&hilo[i], NULL, mihilo, (void*)i);
    }

    for (i=0; i < SIZE; i++) {
        printf("Num[i]: %d", nums[i]);
    }

    exit(0);
}

