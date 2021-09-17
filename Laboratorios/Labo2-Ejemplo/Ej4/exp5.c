#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>

#define NUMHILOS 5

void main() {

    void *funcion(void *data) {
        unsigned long int pthid;
        pthid = pthread_self();

        while (1) {
            printf("Soy el thread %d con identificación %lu correspondiente al proceso %d \n", data, pthid, getpid());

        }
    }

    printf("Comienza a ejecutarse el proceso %d \n", getpid());

    int i;
    pthread_t hilos[NUMHILOS];

    for (i = 0; i < NUMHILOS; i++) {
        printf("Se crea un nuevo thread \n");
        pthread_create(&hilos[i], NULL, funcion, (void *)i);
    }

    for (i = 0; i < NUMHILOS; i++) {
        printf("Finaliza el thread \n");
        pthread_join(hilos[i], NULL);
    }
    
    

}