#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "invalid arguments\n");
        exit(1);
    }

    struct addrinfo hints =
    {
        .ai_family = AF_INET,
        .ai_socktype = SOCK_STREAM
    };
    struct addrinfo *res = NULL;
    if (getaddrinfo(argv[1], argv[2], &hints, &res) < 0) {
        fprintf(stderr, "getaddrinfo failed: %s\n", strerror(errno));
        exit(1);
    }

    int fd = socket(PF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        fprintf(stderr, "socket failed: %s\n", strerror(errno));
        exit(1);
    }
    if (connect(fd, res->ai_addr, res->ai_addrlen) < 0) {
        fprintf(stderr, "connect failed: %s\n", strerror(errno));
        exit(1);
    }
    freeaddrinfo(res);
    int v = 1;
    write(fd, &v, sizeof(v));
    while (read(fd, &v, sizeof(v)) == sizeof(v)) {
        if (v >= 10) break;
        printf("%d\n", v);
        ++v;
        write(fd, &v, sizeof(v));
    }
    close(fd);
    return 0;
}
