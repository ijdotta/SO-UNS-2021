/*
Un proceso padre debe crear dos procesos hijos, uno de ellos ejecutar
el comando de listar un directorio (usar el /etc), y el otro mostrar en
pantalla un contador (de 1 a 10000). El padre deberá esperar la
finalización de ambos procesos, y cuando esto ocurra lo indicará con un
mensaje en pantalla.
• Primer caso: en el proceso padre se encuentra toda la codificación.
• Segundo caso: cada proceso hijo carga una imagen ejecutable para
realizar la tarea asignada.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

//#define CASO1
#define CASO2

#define IT_C1 5

#ifdef CASO1

int main(int argc, char const *argv[]) {

    // hijo1

    pid_t pid1, pid2;

    pid1 = fork();

    if (pid1 == 0) {
        // hijo 1:

        for (int i = 1; i < IT_C1; i++) {
            printf("%d\n", i);
        }

    } 
    else {
        pid2 = fork();

        if (pid2 == 0) {
            // hijo 2:
            system("ls /etc");
        }
        else {

            wait(NULL);
            wait(NULL);

            printf("Terminaron ambos procesos\n");

        }

    }


    return 0;
}

#endif

#ifdef CASO2

int main(int argc, char const *argv[])
{

    pid_t pid1, pid2;

    pid1 = fork();
    if (pid1 == 0) {
        
        char * args[] = {"./iterar", "5", NULL};
        execv(args[0], args);

    }
    else {
        pid2 = fork();

        if (pid2 == 0) {
            execlp("ls", "ls", "/etc", NULL);
        }
        else {
            wait(NULL);
            wait(NULL);
            printf("Fin de ambos procesos\n");
        }
    }

    return 0;
}


#endif
