#include <stdio.h>
#include <stdlib.h>

/*
• El segundo hijo debe mostrar por pantalla el contenido del directorio actual,
esto lo debe realizar 1000 veces, además en cada iteración debe agregar la
siguiente información en el archivo salida.txt ``Estoy mostrando el directorio
actual"
*/

int main(int argc, char const *argv[])
{
    if (argc != 2) {
        printf("Wrong number of args in iterar_y_operar\n");
        exit(1);
    }

    FILE * foutput = fopen("salida.txt", "a");

    int count = atoi(argv[1]);
    for (int i = 0; i < count; i++) {

        system("ls");
        fprintf(foutput, "Estoy mostrando el directorio actual.\n");

    }

    fclose(foutput);
    return 0;
}
