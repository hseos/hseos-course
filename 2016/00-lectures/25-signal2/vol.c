#include <signal.h>
#include <stdio.h>
#include <unistd.h>

volatile sig_atomic_t flag;

void handler(int s)
{
    printf("!\n");
    flag = 1;
}

int main()
{
    sigset_t ss, os;
    sigemptyset(&ss);
    sigaddset(&ss, SIGINT);
    sigemptyset(&os);
    sigprocmask(SIG_BLOCK, &ss, NULL);
    signal(SIGINT, handler);
    while (1) {
        while (!flag) { 
            // ....
            //pause();
            //sigprocmask(SIG_SETMASK, &os, &ss);
            //pause();
            //sigprocmask(SIG_BLOCK, &ss, NULL);
            sigsuspend(&os);
        }
        printf("Arrived\n");
        flag = 0;
    }
}
