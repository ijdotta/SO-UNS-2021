#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define N 6

void main() {
    int A[N], B[N];
    FILE * output;
    FILE * input;

    int pid = fork();
    if (pid == 0) {
        // P2
        printf("P2\n");
        for (int i = 0; i < N; i++) {
            A[i] = i*2;
            B[i] = i+20;
        }
    }
    else {
        pid = fork();
        if (pid == 0) {
            // P3
            printf("P3\n");
            output = fopen("output", "w");

            for (int i = 0; i < N; i++) {
                int sum = A[i] + B[i];
                fprintf(output, "i=%d, ", sum);
            }

            fclose(output);
        }
        else {
            pid = fork();
            if (pid == 0) {
                // P4
                printf("P4\n");
                input = fopen("output", "r");

                while (!feof(input)) {
                    char buffer[25];
                    fscanf(input, "%25s", buffer);
                    printf("%s", buffer);
                }

                fclose(input);

            }
        }
    }
}