#include <signal.h>
#include <stdio.h>
#include <sys/signalfd.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    sigset_t ss;
    sigemptyset(&ss);
    sigaddset(&ss, SIGINT);
    sigaddset(&ss, SIGQUIT);
    sigfillset(&ss);
    sigprocmask(SIG_BLOCK, &ss, NULL);
    int sfd = signalfd(-1, &ss, 0);
    if (sfd < 0) abort();
    struct signalfd_siginfo buf;
    while (1) {
        int r = read(sfd, &buf, sizeof(buf));
        printf("%d: %d\n", r, buf.ssi_signo);
    }
}
