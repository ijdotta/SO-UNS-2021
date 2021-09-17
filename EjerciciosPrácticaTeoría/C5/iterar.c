#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    if (argc != 2) {
        printf("Error. ");
        return(1);
    }

    int count = atoi(argv[1]);

    for (int i = 1; i <= count; i++) {
        printf("%d\n", i);
    }

    return 0;
}
