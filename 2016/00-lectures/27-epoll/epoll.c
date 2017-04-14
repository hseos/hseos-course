#include <sys/epoll.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/signalfd.h>

volatile sig_atomic_t child_flag;

void child_handler(int s)
{
    child_flag = 1;
}

int main(void)
{
    int efd = epoll_create1(EPOLL_CLOEXEC);
    struct epoll_event eev = { .events = EPOLLIN, .data = { .fd = 0 } };
    epoll_ctl(efd, EPOLL_CTL_ADD, 0, &eev);
    fcntl(0, F_SETFL, fcntl(0, F_GETFL) | O_NONBLOCK);

    sigset_t is;
    sigemptyset(&is);
    sigaddset(&is, SIGINT);
    int sfd = signalfd(-1, &is, 0);
    eev = (struct epoll_event) { .events = EPOLLIN, .data = { .fd = sfd } };
    epoll_ctl(efd, EPOLL_CTL_ADD, sfd, &eev);

    sigset_t ss, os;
    sigemptyset(&os);
    sigaddset(&os, SIGINT);
    sigfillset(&ss);
    sigprocmask(SIG_BLOCK, &ss, NULL);
    signal(SIGCHLD, child_handler);

    while (1) {
        int n = epoll_pwait(efd, &eev, 1, 1000, &os);
        if (n < 0 && errno == EINTR && child_flag) {
            child_flag = 0;
            int status;
            int pid = wait(&status);
            printf("Process %d exited\n", pid);
        }
        if (n < 0) {
            printf("Error: %s\n", strerror(errno));
        }
        printf("retval: %d\n", n);
        if (n == 1) {
            if (eev.events == EPOLLIN && eev.data.fd == sfd) {
                struct signalfd_siginfo si;
                int sz = read(sfd, &si, sizeof(si));
                printf("%d %d\n", sz, si.ssi_signo);
            }
            if (eev.events == EPOLLIN && eev.data.fd == 0) {
                while (1) {
                    char buf[128];
                    int sz = read(0, buf, sizeof(buf));
                    if (sz == -1) break;
                    int len = strlen(buf);
                    while (len > 0 && isspace(buf[len - 1])) --len;
                    buf[len] = 0;
                    printf("<%.*s>\n", len, buf);
                    if (!strcmp(buf, "start")) {
                        if (!fork()) {
                            printf("Started: %d\n", getpid());
                            sleep(10);
                            printf("Completed: %d\n", getpid());
                            exit(0);
                        }
                    }
                }
            }
        }
    }
}
