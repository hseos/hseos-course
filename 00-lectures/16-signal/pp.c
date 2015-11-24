#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <sched.h>

int p[2], pid;

int myfork()
{
    int pid = fork();
    if (pid > 0) sched_yield();
    return pid;
}

void handler(int s)
{
    int v;
    if (!pid) pid = getppid();
    read(p[0], &v, sizeof(v));
    printf("%d %d\n", getpid(), v);
    ++v;
    write(p[1], &v, sizeof(v));
    kill(pid, SIGUSR1);
}

int main()
{
    pipe(p);
    signal(SIGUSR1, handler);
    if (!(pid = fork())) {
        // son
        pid = getppid();
        while (1) pause();
    } else {
        // parent
        int v = 1;
        write(p[1], &v, sizeof(v));
        kill(pid, SIGUSR1);
        while (1) sleep(1);
    }
}
