#include <signal.h>
#include <stdio.h>
#include <unistd.h>

// ping-pong отца и сына с помощью одного pipe и одного сигнала

int fd[2];
int pid;

void handler(int s)
{
    int x;
    if (!pid) pid = getppid();
    read(fd[0], &x, sizeof(x));
    printf("%d %d\n", getpid(), x); fflush(stdout);
    ++x;
    write(fd[1], &x, sizeof(x));
    kill(pid, SIGUSR1);
}

int main(void)
{
    pipe(fd);
    signal(SIGUSR1, handler);
    if (!(pid = fork())) {
        while (1) pause();
    }

    int z = 1;
    write(fd[1], &z, sizeof(z));
    kill(pid, SIGUSR1);
    while (1) pause();
}
