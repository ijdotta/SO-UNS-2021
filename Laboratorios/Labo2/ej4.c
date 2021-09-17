#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


#define NUMHILOS 7

int a=0; //es una variable global

void *funcion (void *data) {
    unsigned long int pthid;
    int j;
    pthid = pthread_self();
    j = 0;
    while (j < 3) {
        a++;
        printf("Soy el thread %d con identificacion %lu correspondiente al proceso %d \n", *((int*)data),
            pthid, getpid());
        j++;
    }
}

void main() {
    printf("Comienza a ejecutarse el proceso %d \n", getpid());

    int i;
    pthread_t hilos[NUMHILOS];

    for (i=0; i < NUMHILOS; i++) {
        printf("Se crea un nuevo thread \n");
        pthread_create(&hilos[i], NULL, funcion, (void *)(&i));
    }
    for (i=0; i < NUMHILOS; i++) {
        printf("Finaliza el thread %d... \n", i);
        pthread_join(hilos[i], NULL);
    }

    printf("a final = %d\n", a);
}
