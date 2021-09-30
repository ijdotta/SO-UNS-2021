#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define A 0
#define B 1
#define C 2
#define D 3
#define E 4
#define F 5

#define PROCESSES 6

#define EXE 1

void process(int i, int * pfd_p, int * pfd_c, ssize_t BUFF_SIZE);

int main(int argc, char const *argv[])
{   
    ssize_t BUFF_SIZE = sizeof(int);
    int pfd_p[PROCESSES][2];
    int pfd_c[PROCESSES][2];

    // Crear procesos y pipes
    for (int i = 0; i < PROCESSES; i++) {

        if (!fork()) {

            printf("Creando hijo %d\n", i);

            pipe(pfd_p[i]);
            pipe(pfd_c[i]);
            process(i, pfd_p[i], pfd_c[i], BUFF_SIZE);
        }
        else {

            printf("Configurando pipe para %d\n", i);

            close(pfd_p[i][0]);
            close(pfd_c[i][1]);
        }

    }

    printf("Pipes y procesos listos\n");

    // Pipes

    int buff = EXE;
    int wait_buff = 0;

    while (1) {

        printf("Previo AB\n");

        int ab = random() % 2;

        if (ab) {
            printf("signal A\n");
            // A
            write(pfd_p[A][1], &buff, BUFF_SIZE);
            read(pfd_c[A][0], &wait_buff, BUFF_SIZE);
        }
        else {
            printf("signal B\n");
            // B
            write(pfd_p[B][1], &buff, BUFF_SIZE);
            read(pfd_c[B][0], &wait_buff, BUFF_SIZE);
        }

        int cd = random() % 2;

        if (cd) {
            // C
            printf("signal C\n");
            write(pfd_p[C][1], &buff, BUFF_SIZE);
            read(pfd_c[C][0], &wait_buff, BUFF_SIZE);
        }
        else {
            // D
            printf("signal D\n");
            write(pfd_p[D][1], &buff, BUFF_SIZE);
            read(pfd_c[D][0], &wait_buff, BUFF_SIZE);
        }

        printf("signal E\n");
        write(pfd_p[E][1], &buff, BUFF_SIZE);
        read(pfd_c[E][0], &wait_buff, BUFF_SIZE);

        printf("signal F\n");
        write(pfd_p[F][1], &buff, BUFF_SIZE);
        read(pfd_c[F][0], &wait_buff, BUFF_SIZE);
    }

    
    return 0;
}

void process(int i, int * pfd_p, int * pfd_c, ssize_t BUFF_SIZE) {
    int execute;

    close(pfd_p[1]);
    close(pfd_c[0]);

    printf("Proceso hijo %d\n", i);

    while (1) {
        printf("while: Proceso hijo %d\n", i);
        read(pfd_p[0], &execute, BUFF_SIZE);
        printf("Soy %d\n", i);
        write(pfd_c[1], &execute, BUFF_SIZE);
    }
}
