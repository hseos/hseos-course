#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>

int main()
{
    int fd = epoll_create1(0);

    struct epoll_event ev = {};
    ev.events = EPOLLIN;
    ev.data.fd = 0;
    epoll_ctl(fd, EPOLL_CTL_ADD, 0, &ev);

    fcntl(0, F_SETFL, fcntl(0, F_GETFL) | O_NONBLOCK);

    enum { EVENT_COUNT = 5 };

    while (1) {
        struct epoll_event evs[EVENT_COUNT];
        int n = epoll_wait(fd, evs, EVENT_COUNT, 1000);
        if (n < 0) {
            perror("epoll");
            exit(1);
        } else if (!n) {
            printf("timeout\n");
        } else {
            printf("events: %d\n", n);
            for (int i = 0; i < EVENT_COUNT; ++i) {
                struct epoll_event *ee = &evs[i];
                if (ee->data.fd == 0) {
                    while (1) {
                        char c;
                        int r = read(0, &c, 1);
                        if (r < 0 && errno == EAGAIN) {
                            break;
                        } else if (r < 0) {
                            // IO error
                        } else if (!r) {
                        } else {
                            printf(">%d<\n", c);
                        }
                    }
                }
            }
        }
    }
}
