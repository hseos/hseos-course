#include <signal.h>
#include <sys/signalfd.h>
#include <stdio.h>
#include <unistd.h>

// использование signalfd (linux-only)

int main()
{
    sigset_t s1, s2;
    sigemptyset(&s1);
    sigaddset(&s1, SIGINT);
    sigprocmask(SIG_BLOCK, &s1, &s2);

    int fd = signalfd(-1, &s1, 0);
    while (1) {
        struct signalfd_siginfo ssi;
        read(fd, &ssi, sizeof(ssi));
        printf("signal\n");
        printf("signo: %d\n", ssi.ssi_signo);
        printf("pid: %d\n", ssi.ssi_pid);
    }
}
