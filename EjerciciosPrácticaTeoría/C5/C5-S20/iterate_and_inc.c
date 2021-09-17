#include <stdio.h>
#include <stdlib.h>

/*
• El tercer hijo debe iterar 20000 veces y en cada una de las iteraciones debe
sumar 1 a una variable entera y lo debe mostrar por pantalla ``El resultado es
...", por último debe agregar esta información en el archivo salida.txt.
*/

int main(int argc, char const *argv[])
{

    if (argc != 2) {
        printf("Wrong number of args in iterate_and_inc\n");
        exit(1);
    }

    FILE * foutput = fopen("salida.txt", "a");

    int i;
    int count = atoi(argv[1]);
    for (i = 0; i < count; i++) {

        printf("El resultado es %d\n", i);
        fprintf(foutput, "El resultado es %d\n", i);

    }

    fclose(foutput);

    return 0;
}
