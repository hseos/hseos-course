#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <sched.h>

int p[2], pid;

volatile sig_atomic_t usrflag = 0;

void handler(int s)
{
    usrflag = 1;
}

int main()
{
    sigset_t ss, os;
    pipe(p);
    sigemptyset(&ss); sigaddset(&ss, SIGUSR1);
    sigprocmask(SIG_BLOCK, &ss, &os);
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
    while (1) {
        sigprocmask(SIG_UNBLOCK, &ss, NULL);
        while (!usrflag) {
            sigsuspend(&os);
        }
        sigprocmask(SIG_BLOCK, &ss, NULL);
        usrflag = 0;
        int v;
        read(p[0], &v, sizeof(v));
        printf("%d %d\n", getpid(), v);
        ++v;
        write(p[1], &v, sizeof(v));
        kill(pid, SIGUSR1);
    }
}
