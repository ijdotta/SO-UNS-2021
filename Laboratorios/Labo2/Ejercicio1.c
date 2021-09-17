#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int pid, pid2;
int main()
{
    int status, s_wait;
    int trata_alarma();
    pid = fork();

    if (pid!=0)
    {

        pid2 = fork();

        if (pid2 != 0) {

            printf("padre = pid=%d... \n", pid2);
            signal(SIGALRM, (void *)(int) trata_alarma);
            alarm(10);
            wait(&status);
            alarm(0);
        }
        else {
            printf("hijo 2 = pid=%d..... \n", pid2);
            while(1){};
            exit(1);
        }
    }
    else
    {
        printf("hijo 1 = pid=%d.... \n", pid);
        while(1){};
        exit(1);
    }
}
    
int trata_alarma()
{
    printf("killing pid=%d", pid);
    kill(pid, SIGKILL);
}