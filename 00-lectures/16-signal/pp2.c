#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <sched.h>

int p[2], pid;

int myfork()
{
    int pid = fork();
    return pid;
}

void handler(int s)
{
    int v;
    read(p[0], &v, sizeof(v));
    printf("%d %d\n", getpid(), v);
    ++v;
    write(p[1], &v, sizeof(v));
    kill(pid, SIGUSR1);
}

int main()
{
    sigset_t ss;
    pipe(p);
    sigemptyset(&ss); sigaddset(&ss, SIGUSR1);
    sigprocmask(SIG_BLOCK, &ss, NULL);
    if (!(pid = fork())) {
        // son
        signal(SIGUSR1, handler);
        pid = getppid();
    } else {
        // parent
        signal(SIGUSR1, handler);
        int v = 1;
        write(p[1], &v, sizeof(v));
        kill(pid, SIGUSR1);
    }
    sigprocmask(SIG_UNBLOCK, &ss, NULL);
    while (1) pause();
}
