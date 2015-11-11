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

int main(int argc, char *argv[])
{
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

    while (1) {
        struct sockaddr_in aa;
        socklen_t slen = sizeof(aa);
        int afd = accept(fd, (struct sockaddr *) &aa, &slen);
        if (afd < 0) {
            fprintf(stderr, "accept failed: %s\n", strerror(errno));
            exit(1);
        }
        printf("ip: %s, port: %d\n", inet_ntoa(aa.sin_addr), ntohs(aa.sin_port));
        while (waitpid(-1, NULL, WNOHANG) > 0) {};
        if (!fork()) {
            close(fd);
            int v;
            while (read(afd, &v, sizeof(v)) == sizeof(v)) {
                printf("%d\n", v);
                ++v;
                //sleep(5);
                write(afd, &v, sizeof(v));
            }
            close(afd);
            exit(1);
        }
    }
}
