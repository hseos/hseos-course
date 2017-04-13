#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int fd = socket(PF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        perror("");
        exit(1);
    }

    int val = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
    setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, &val, sizeof(val));

    struct sockaddr_in sa;
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = INADDR_ANY;
    sa.sin_port = htons(12347);
    if (bind(fd, (void*) &sa, sizeof(sa)) < 0) {
        perror("");
        exit(1);
    }

    if (listen(fd, 5) < 0) {
        perror("");
        exit(1);
    }

    while (1) {
        struct sockaddr_in ss;
        size_t sz = sizeof(ss);
        int afd = accept(fd, (void*) &ss, &sz);
        if (afd < 0) {
            perror("");
            exit(1);
        }

        if (!fork()) {
            close(fd);
            printf("client: %s, %d\n", inet_ntoa(ss.sin_addr), ntohs(ss.sin_port));

            char c;
            write(afd, "go on\r\n", 7);

            while (read(afd, &c, 1) == 1) {
                putchar(c);
                write(afd, &c, 1);
            }
            exit(0);
        }
        close(afd);
    }
}
