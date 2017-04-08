#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sched.h>

int fds[2];
int pid;

void handler(int s)
{
    if (!pid) pid = getppid();
    int x;
    read(fds[0], &x, sizeof(x));
    printf("%d %d\n", getpid(), x);
    ++x;
    write(fds[1], &x, sizeof(x));
    kill(pid, SIGUSR1);
}

int main()
{
    pipe(fds);
    signal(SIGUSR1, handler);
    if (!(pid = fork())) {
        pid = getppid();
        while (1) {
            pause();
        }
    }
    int z = 0;
    write(fds[1], &z, sizeof(z));
    kill(pid, SIGUSR1);
    while (1) {
        pause();
    }
}
