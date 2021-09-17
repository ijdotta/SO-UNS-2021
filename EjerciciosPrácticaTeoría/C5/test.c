#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    /*
    char * args[] = {"./iterar", "5", NULL};
        // char * env = {"0"};

    execvp(args[0], args);
*/
    char * args[] = {"./iterar", "5", NULL};
        // char * env = {"0"};

    execv(args[0], args);
    
    return 0;
}
