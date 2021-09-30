#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int pfd_p[2], pfd_c[2];

    pipe(pfd_p);
    pipe(pfd_c);

    ssize_t SIZE = sizeof(int);

    if (fork()) {
        // padre
        close(pfd_p[0]);
        close(pfd_c[1]);
        int buff = 0;

        while (1) {
            write(pfd_p[1], &buff, SIZE);
            read(pfd_c[0], &buff, SIZE);
            printf("Padre: %d\n", buff);
        }
    }
    else {
        // hijo
        close(pfd_p[1]);
        close(pfd_c[0]);

        int buff = 0;
        while (1) {
            read(pfd_p[0], &buff, SIZE);
            printf("Hijo: %d\n", buff);
            ++buff;
            write(pfd_c[1], &buff, SIZE);
        }

    }

    return 0;
}
