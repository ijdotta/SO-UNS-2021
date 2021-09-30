#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#define N 5

// definición de matrices
int A[N][N];
int B[N][N];
int C[N][N];

void * fnSumarFila(void * args) {
    int fila = *((int *) args);

    for (int i = 0; i < N; i++) {
        printf("sumando fila=%d, i=%d\n", fila, i);
        C[fila][i] = A[fila][i] + B[fila][i];
    }

    pthread_exit(NULL);
}

int main(int argc, char const *argv[]) {

    // inicialización
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = 1;
            B[i][j] = 2;
        }
    }

    // crear N hilos y calcular filas i

    pthread_t hilo[N];

    int i = 0;
    while (i < N) {
        
        pthread_create(&hilo[i], NULL, fnSumarFila, (void*) &i);

        i++;
    }

    // esperar a los 5 hilos
    for(int i = 0; i < N; i++) {
        pthread_join(hilo[i], NULL);
    }

    // print matrix:

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

}