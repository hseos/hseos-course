#include <signal.h>
#include <stdio.h>
#include <unistd.h>

// корректное ожидание поступления сигнала с помощью sigsuspend

volatile sig_atomic_t flag = 0;

void handler(int s)
{
    flag = 1;
}

int main()
{
    sigaction(SIGINT, 
                &(struct sigaction){ .sa_handler = handler, 
                                    .sa_flags = SA_RESTART }, NULL);
    sigset_t s1, s2;
    sigemptyset(&s1);
    sigaddset(&s1, SIGINT);
    sigprocmask(SIG_BLOCK, &s1, &s2);

    while (1) {
        while (!flag) {
            sigsuspend(&s2);
        }
        printf("signal %d\n", getpid());
        flag = 0;
    }
}
