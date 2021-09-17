#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

#define SIZE 5

int nums[SIZE] = {0,1,2,3,4};

int main() {
    int i;
    pid_t pid = fork();

    if (pid == 0) {
        for (i = 0; i < SIZE; i++) {
            nums[i] = 2*i;
            printf("Num[i]: %d ", nums[i]);
        }
    }
    else if (pid > 0) {
        for (i = 0; i < SIZE; i++) {
            printf("Padre: %d ", nums[i]);
        }
    }
}