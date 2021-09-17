#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int pid;
int main()
{
    int status, s_wait;
    int trata_alarma();
    pid = fork();

    printf("pid=%d", pid);

    if (pid!=0)
    {

        pid = fork();

        if (pid != 0) {

            printf("... \n");
            signal(SIGALRM, (void *)(int) trata_alarma);
            alarm(10);
            wait(&status);
            alarm(0);
        }
        else {
            printf(".... \n");
            while(1){};
            exit(1);
        }
    }
    else
    {
        printf(".... \n");
        while(1){};
        exit(1);
    }
}
    
int trata_alarma()
{
    printf("killing pid=%d", pid);
    kill(pid, SIGKILL);
}