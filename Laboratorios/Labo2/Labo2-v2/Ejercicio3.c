#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#define N 5

int main(int argc, char const *argv[]) {

    // definición de matrices
    int A[N][N];
    int B[N][N];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 5; j++) {
            A[i][j] = 1;
            B[i][j] = 2;
        }
    }

    // crear N procesos y calcular filas i
    int i = 0;
    while (i < N) {
        pid_t pid = fork();

        printf("pid=%d\n", pid);

        if (pid == 0) {

            printf("Estoy en el hijo %d\n", i);

            FILE * sumafila;
            char filename[50];
            printf("Estoy en el hijo %d otra vez\n", i);

            sprintf(filename, "%s%d%s", "SumaFila(", i, ").txt");
            printf("filename: %s\n", filename);

            sumafila = fopen(filename, "w");

            // calcular fila i + write
            for (int j = 0; j < N; j++) {
                int sum = A[i][j] + B[i][j];
                printf("suma = %d \n", sum);

                char value[4];
                sprintf(value, "%d", sum);
                fprintf(sumafila, "%s\n", value);
                
            }

            fclose(sumafila);
            exit(0);
        }

        i++;
    }

    // esperar a los 5 hijos
    for(int i = 0; i < N; i++) {
        wait(NULL);
    }

    // construir matriz final:
    int C[N][N];

    for (int i = 0; i < N; i++) {
        FILE * file;

        char filename[50];
        sprintf(filename, "%s%d%s", "SumaFila(", i, ").txt");

        printf("loading results from file %s\n", filename);

        file = fopen(filename, "r");

        int j = 0;
        while (!feof(file) && j < N) {
            char val[2];
            fgets(val, 5, file); // 5 es un número arbitrario, va a tomar caracteres solo hasta el final de línea
            printf("file %d, val=%s\n", i, val);
            C[i][j] = atoi(&val[0]);
            j++;
        }

        fclose(file);
    }

    // print matrix:

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

}