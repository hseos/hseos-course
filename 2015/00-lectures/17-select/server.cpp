#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/select.h>
#include <map>
#include <set>
#include <sys/time.h>
#include <limits.h>


using namespace std;

struct State
{
    int fd = -1;
    char state = 'R';
    int value = 0;
    long long wakeup;

    State(int fd_) : fd(fd_) {}
};

int main(int argc, char *argv[])
{
    signal(SIGPIPE, SIG_IGN);

    if (argc != 2) {
        fprintf(stderr, "invalid arguments\n");
        exit(1);
    }
    int port = strtol(argv[1], 0, 10);
    if (port < 0 || port > 65535) {
        fprintf(stderr, "invalid port\n");
        exit(1);
    }
    int fd = socket(PF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        fprintf(stderr, "socket failed: %s\n", strerror(errno));
        exit(1);
    }

    int opt = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in ba;
    ba.sin_family = AF_INET;
    ba.sin_port = htons(port);
    ba.sin_addr.s_addr = INADDR_ANY;
    if (bind(fd, (struct sockaddr*) &ba, sizeof(ba)) < 0) {
        fprintf(stderr, "bind failed: %s\n", strerror(errno));
        exit(1);
    }

    if (listen(fd, 10) < 0) {
        fprintf(stderr, "listen failed: %s\n", strerror(errno));
        exit(1);
    }

    fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK);

    map<int, State> states;

    while (1) {
        fd_set rs, ws;
        set<int> dels;
        FD_ZERO(&rs); FD_ZERO(&ws);
        FD_SET(fd, &rs);
        for (auto &sts : states) {
            if (sts.second.state == 'R') {
                FD_SET(sts.second.fd, &rs);
            }
            if (sts.second.state == 'W') {
                FD_SET(sts.second.fd, &ws);
            }
        }
        
        struct timeval cv;
        gettimeofday(&cv, NULL);
        long long current = cv.tv_sec * 1000LL + cv.tv_usec / 1000;
        long long waittime = LONG_LONG_MAX;
        for (auto &sts : states) {
            if (sts.second.state == 'S') {
                long long diff = sts.second.wakeup - current;
                if (diff < 0) diff = 0;
                if (diff < waittime) waittime = diff;
            }
        }
        struct timespec ww, *pw = NULL;
        if (waittime != LONG_LONG_MAX) {
            ww.tv_sec = waittime / 1000;
            ww.tv_nsec = waittime % 1000 * 1000000;
            pw = &ww;
        }

        int r = pselect(FD_SETSIZE, &rs, &ws, NULL, pw, NULL);
        gettimeofday(&cv, NULL);
        current = cv.tv_sec * 1000LL + cv.tv_usec / 1000;
        if (r < 0 && errno == EINTR) {
            fprintf(stderr, "interrupt!\n");
            continue;
        }
        if (r < 0) {
            fprintf(stderr, "pselect failed: %s\n", strerror(errno));
            exit(1);
        }
/*
        if (!r) {
            fprintf(stderr, "timeout!\n");
            continue;
        }
*/
        for (auto &sts : states) {
            if (sts.second.state == 'S' && current >= sts.second.wakeup) {
                sts.second.state = 'W';
            }
        }
        if (FD_ISSET(fd, &rs)) {
            while (1) {
                struct sockaddr_in aa;
                socklen_t slen = sizeof(aa);
                int afd = accept(fd, (struct sockaddr *) &aa, &slen);
                if (afd < 0 && errno == EAGAIN) break;
                if (afd < 0) {
                    fprintf(stderr, "accept failed: %s\n", strerror(errno));
                    exit(1);
                }
                printf("ip: %s, port: %d\n", inet_ntoa(aa.sin_addr), ntohs(aa.sin_port));
                states.insert(make_pair(afd, State(afd)));
            }
        }
        dels.erase(dels.begin(), dels.end());
        for (auto &sts : states) {
            if (sts.second.state == 'R' && FD_ISSET(sts.second.fd, &rs)) {
                int v;
                int r = read(sts.second.fd, &v, sizeof(v));
                if (r == sizeof(v)) {
                    printf("%d %d\n", sts.second.fd, v);
                    ++v;
                    //sts.second.state = 'W';
                    sts.second.value = v;
                    sts.second.state = 'S';
                    sts.second.wakeup = current + 100;
                }
                if (r == 0) {
                    printf("%d close\n", sts.second.fd);
                    dels.insert(sts.second.fd);
                }
                if (r < 0 && errno != EAGAIN) {
                    fprintf(stderr, "%d error %s\n", sts.second.fd, strerror(errno));
                    dels.insert(sts.second.fd);
                }
            }
        }
        for (auto &sts : states) {
            if (sts.second.state == 'W' && FD_ISSET(sts.second.fd, &ws)) {
                int v = sts.second.value;
                int w = write(sts.second.fd, &v, sizeof(v));
                if (w == sizeof(v)) {
                    sts.second.state = 'R';
                }
                if (w < 0 && errno != EAGAIN) {
                    fprintf(stderr, "%d error %s\n", sts.second.fd, strerror(errno));
                    dels.insert(sts.second.fd);
                }
            }
        }
        for (int fd : dels) {
            close(fd);
            states.erase(fd);
        }
    }
}
