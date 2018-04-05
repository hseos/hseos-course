#include <signal.h>
#include <stdio.h>
#include <unistd.h>

// ping-pong отца и сына с блокировкой сигналов

int fd[2];
int pid;

void handler(int s)
{
    int x;
    read(fd[0], &x, sizeof(x));
    printf("%d %d\n", getpid(), x); fflush(stdout);
    ++x;
    write(fd[1], &x, sizeof(x));
    kill(pid, SIGUSR1);
}

int main(void)
{
    sigset_t s1, s2;
    sigemptyset(&s1);
    sigaddset(&s1, SIGUSR1);
    sigprocmask(SIG_BLOCK, &s1, &s2);
    pipe(fd);
    if (!(pid = fork())) {
        pid = getppid();
        signal(SIGUSR1, handler);
        while (1) {
            sigsuspend(&s2);
        }
    }

    signal(SIGUSR1, handler);
    int z = 1;
    write(fd[1], &z, sizeof(z));
    kill(pid, SIGUSR1);
    while (1) {
        sigsuspend(&s2);
    }
}
