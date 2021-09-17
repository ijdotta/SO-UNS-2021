#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

void main (int argc, char argv) {

    fflush(stdin);

    printf("argc=%d\n", argc);

    int i;
    printf("cond=%d\n", (i <= argc));
    for (i = 1; i <= argc; i++) {
        fork();
        printf("(i=%d), (pid=%d) \n", i, getpid());
    }
}

/*En cada iteración el proceso padre se duplica, por lo tanto, en la iteración i hay 2^i printf(i, pid)*/