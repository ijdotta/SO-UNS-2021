/*
Un proceso padre debe crear tres HILOS hijos. El padre crea un archivo
denominado salida.txt antes de invocar a los HILOS hijos. El proceso padre
debe esperar que los HILOS hijos terminen su ejecución y al finalizar debe
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
#include <pthread.h>

void newTask(char * path, char * arg) {
    /*
    char * args[] = {path, arg, NULL};
    execv(args[0], args);
    */
}

void * tarea1(void * data) {
    //newTask("./iterar_y_operar", "5");
    system("./iterar_y_operar 5");
    pthread_exit(NULL);
}

void * tarea2(void * data) {
    //newTask("./ls_and_write", "5");
    system("./ls_and_write 5");
    pthread_exit(NULL);
}

void * tarea3(void * data) {
    //newTask("./iterate_and_inc", "5");
    system("./iterate_and_inc 5");
    pthread_exit(NULL);
}

int main(int argc, char const *argv[]) {

    // crear archivo
    FILE * foutput = fopen("salida.txt", "a");

    // asignar tareas

    pthread_t hilo[3];

    pthread_create(&hilo[0], NULL, tarea1, NULL);
    pthread_create(&hilo[1], NULL, tarea2, NULL);
    pthread_create(&hilo[2], NULL, tarea3, NULL);

    // esperar finalización hijos
    for (int i = 0; i < 3; i++) {
        pthread_join(hilo[i], NULL);
    }

    // escribir salida
    fprintf(foutput, "Se ha finalizado la actividad\n");
    fclose(foutput);

    printf("FIN\n");

    return 0;
}
