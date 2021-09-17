/*
• El primer hijo debe realizar un ciclo de 100000 iteraciones, en cada una de
las iteraciones realiza cuatro operaciones aritméticas y agregar el texto
“Operaciones aritméticas” en el archivo salida.txt.
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{

    if (argc != 2) {
        printf("Wrong number of args in iterar_y_operar\n");
        exit(1);
    }

    // archivo
    FILE * foutput = fopen("salida.txt", "a");

    int count = atoi(argv[1]);
    for (int i = 1; i <= count; i++) {
        
        int sum = i + i;
        int subt = i - count;
        int div = (int) (i / count);
        int mul = i * 5;

        fprintf(foutput, "Operaciones aritméticas (i=%d) => sum(%d) ; subt(%d) ; div(%d) ; mul(%d)\n", i, sum, subt, div, mul);
    }

    fclose(foutput);
    return 0;
}
