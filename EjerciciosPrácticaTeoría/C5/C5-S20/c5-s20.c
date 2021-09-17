/*
Un proceso padre debe crear tres procesos hijos. El padre crea un archivo
denominado salida.txt antes de invocar a los procesos hijos. El proceso padre
debe esperar que los procesos hijos terminen su ejecución y al finalizar debe
agregar en el archivo salida.txt ``Se ha finalizado la actividad". Cada proceso
hijo debe cargar una imagen ejecutable que realice la tarea asignada:
• El primer hijo debe realizar un ciclo de 100000 iteraciones, en cada una de
las iteraciones realiza cuatro operaciones aritméticas y agregar el texto
“Operaciones aritméticas” en el archivo salida.txt.
• El segundo hijo debe mostrar por pantalla el contenido del directorio actual,
esto lo debe realizar 1000 veces, además en cada iteración debe agregar la
siguiente información en el archivo salida.txt ``Estoy mostrando el directorio
actual"
• El tercer hijo debe iterar 20000 veces y en cada una de las iteraciones debe
sumar 1 a una variable entera y lo debe mostrar por pantalla ``El resultado es
...", por último debe agregar esta información en el archivo salida.txt.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void newTask(char * path, char * arg) {

    pid_t pid = fork();

    if (pid == 0) {
        char * args[] = {path, arg, NULL};
        execv(args[0], args);
    }
}

int main(int argc, char const *argv[]) {

    // crear archivo
    FILE * foutput = fopen("salida.txt", "a");

    // asignar tareas
    int child_count = 0;

    newTask("./iterar_y_operar", "100000");
    child_count++;

    newTask("./ls_and_write", "1000");
    child_count++;

    newTask("./iterate_and_inc", "20000");
    child_count++;

    // esperar finalización hijos
    while (child_count != 0) {
        wait(NULL);
        child_count--;
    }

    // escribir salida
    fprintf(foutput, "Se ha finalizado la actividad\n");
    fclose(foutput);

    return 0;
}
