#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define CANT_HOMBRES 10
#define CANT_MUJERES 10

void * mujer(void * data);
void * hombre(void * data);

sem_t h_mutex, m_mutex, hm_mutex, mujer_count, hombre_count;

int main(int argc, char const *argv[])
{
    // Crear semáforos
    sem_init(&hm_mutex, 0, 1);
    sem_init(&h_mutex, 0, 1);
    sem_init(&m_mutex, 0, 1);
    sem_init(&hombre_count, 0, 0);
    sem_init(&mujer_count, 0, 0);

    // Declaración de threads
    pthread_t hombres[10];
    pthread_t mujeres[10];

    // Creación de threads

    for (int i = 0; i < 10; i++){
        pthread_create(&hombres[i], NULL, hombre, (void *) &i);
    }

    for (int i = 0; i < CANT_MUJERES; i++) {
        pthread_create(&mujeres[i], NULL, mujer, (void *) &i);
    }
    

    // Finalizar hilos
    for (int i = 0; i < 10; i++){
        pthread_join(hombres[i], NULL);
    }

    for (int i=0; i < 10; i++){
        pthread_join(mujeres[i], NULL);
    }

    // Destruir semáforos
    sem_destroy(&hm_mutex);
    sem_destroy(&h_mutex);
    sem_destroy(&m_mutex);
    sem_destroy(&hombre_count);
    sem_destroy(&mujer_count);

    pthread_exit(NULL);

    return 0;
}

/**
 * Función para simular tiempos de baño variables
*/
void usarBanio() {
    int banio_time = random() % 10;
    printf("usa el baño durante %d segundos.\n", banio_time);
    sleep(banio_time);
}

/**
 * Función para simular que una persona no va al baño ni bien sale
*/
void noVoyAlBanio() { 
    int banio_time = random() % 10;
    printf("no voy al baño durante %d segundos.\n", banio_time);
    sleep(banio_time);
}

void * mujer(void * data) {

    int mujer_index = *((int *) data);
while(1) { 

    // Sección crítica: entrar al baño mujer
    sem_wait(&m_mutex);
    if (sem_trywait(&mujer_count) ) {
        printf("No hay mujeres en el baño. Esperando a que no haya hombres...\n");
        sem_wait(&hm_mutex);
    }
    else {
        sem_post(&mujer_count);         // devolver la mujer que saqué extra
    }
    sem_post(&mujer_count);             // entra una mujer
    sem_post(&m_mutex);
    // Fin sección crítica

    printf("La mujer %d ", mujer_index);
    usarBanio();
    
    // Sección crítica: salir del baño mujer.
    sem_wait(&m_mutex);
    sem_wait(&mujer_count);                 // sale una mujer

    if (sem_trywait(&mujer_count)) {
        sem_post(&hm_mutex);
        printf("Salió la última mujer (%d). Avisando a los hombres que ahora pueden entrar...\n", mujer_index);
    }
    else {
        sem_post(&mujer_count);         // si no fue la última mujer, "devolver" la mujer que saqué extra
        printf("Salió una mujer (%d), pero todavía hay otras en el baño.\n", mujer_index);
    }
    sem_post(&m_mutex);
    // Fin sección crítica


    printf("Soy mujer (%d) y ", mujer_index);
    noVoyAlBanio();
}
}

void * hombre(void * data) {

    int hombre_index = *((int *) data);
while(1) {
    // Sección crítica: entrar al baño hombre
    sem_wait(&h_mutex);
    if (sem_trywait(&hombre_count) ) {
        printf("No hay hombres en el baño. Esperando a que no haya mujeres...\n");
        sem_wait(&hm_mutex);
    }
    else {
        sem_post(&hombre_count);         // devolver el hombre que saqué extra
    }
    sem_post(&hombre_count);             // entra un hombre
    sem_post(&h_mutex);
    // Fin sección crítica

    printf("El hombre %d ", hombre_index);
    usarBanio();
    
    // Sección crítica: salir del baño hombre.
    sem_wait(&h_mutex);
    sem_wait(&hombre_count);                 // sale un hombre

    if (sem_trywait(&hombre_count)) {
        sem_post(&hm_mutex);
        printf("Salió el último hombre (%d). Avisando a las mujeres que ahora pueden entrar...\n", hombre_index);
    }
    else {
        sem_post(&hombre_count);         // si no fue el último hombre, "devolver" el hombre que saqué extra
        printf("Salió un hombre (%d), pero todavía hay otros en el baño.\n", hombre_index);
    }
    sem_post(&h_mutex);
    // Fin sección crítica

    printf("Soy hombre (%d) y ", hombre_index);
    noVoyAlBanio();
}
}