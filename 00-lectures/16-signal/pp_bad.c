#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <sched.h>

int p[2], pid;

// оболочка над fork(), в которой приоритет выполнения отдается сыну
int myfork()
{
    int pid = fork();
    if (pid > 0) sched_yield();
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

// функция с разнообразными ошибками синхронизации
int main()
{
    pipe(p);
    if (!(pid = fork())) {
        // son
        signal(SIGUSR1, handler);
        pid = getppid();
        while (1) pause();
    } else {
        // parent
        signal(SIGUSR1, handler);
        int v = 1;
        write(p[1], &v, sizeof(v));
        kill(pid, SIGUSR1);
        while (1) sleep(1);
    }
}
