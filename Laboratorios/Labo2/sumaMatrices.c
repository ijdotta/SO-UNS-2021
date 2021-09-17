/*
#include <sys/types.h>
#include <unistd.h>
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 5

int ** leerMatriz(char * path) {
    FILE * file;
    fopen(path, "r");

    int matrix[5][5];
    int line = 0;

    /*
        1 2 3 4 5
        1 2 3 4 5 
        1 2 3 4 5 
        1 2 3 4 5 
        1 2 3 4 5 
    */

    while(!feof(file)) {
        char buffer[N*2];
        fscanf(file, "%9s", buffer);

        for (int i = 0; i < N; i++) {
            matrix[line][i] = atoi(&buffer[i*2]);
        }
        line++;
    }

    fclose(file);

    return matrix;
}

void printMatrix(int ** matrix) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; i < N; j++) {
            printf("%d, ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {

    // leer matrices A y B
    FILE * fileA, fileB;
    int ** A, ** B;

    A = leerMatriz(argv[1]);
    B = leerMatriz(argv[2]);
    
    printMatrix(A);
    // 5 fork para 5 filas

    // juntar el resultado

}

