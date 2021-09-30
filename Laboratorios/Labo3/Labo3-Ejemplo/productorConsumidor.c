#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

#define BUFFER_SIZE 20
#define PRODUCERS 3
#define CONSUMERS 3

void * fn_producer(void * data);
void * fn_consumer(void * data);

sem_t mutex, full, empty, wrt;

int main(int argc, char const *argv[])
{

    // Crear semáforos de sincronización
    sem_init(&mutex, 0, 1);
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, BUFFER_SIZE);

    // Crear hilos productores
    pthread_t producer[PRODUCERS];
    for (int i = 0; i < PRODUCERS; i++) {
        pthread_create(&producer[i], NULL, &fn_producer, NULL);
    }

    // Crear hilos consumidores
    pthread_t consumer[CONSUMERS];
    for (int i = 0; i < CONSUMERS; i++) {
        pthread_create(&consumer[i], NULL, &fn_consumer, NULL);
    }

    // Finalizar hilos
    for (int i = 0; i < PRODUCERS; i++) {
        pthread_join(&producer[i], NULL);
    }

    for (int i = 0; i < CONSUMERS; i++) {
        pthread_join(&consumer[i], NULL);
    }

    // Destruir semáforos
    sem_destroy(&empty);
    sem_destroy(&full);
    
    
    return 0;
}

void * fn_consumer(void * data) {
    sem_wait(&full);

    // consume item

    sem_post(&empty);
}

void * fn_producer(void * data) {
    sem_wait(&empty);

    // produce item

    sem_post(&full);
}

