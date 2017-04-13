#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int fd = socket(PF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        perror("");
        exit(1);
    }
    unsigned char b1, b2, b3, b4;
    sscanf(argv[1], "%hhu.%hhu.%hhu.%hhu", &b1, &b2, &b3, &b4);
    unsigned char ipbuf[4] = { b1, b2, b3, b4 };
    int port;
    sscanf(argv[2], "%d", &port);

    struct sockaddr_in aa;
    aa.sin_family = AF_INET;
    aa.sin_port = htons(port);
    memcpy(&aa.sin_addr, ipbuf, 4);
    if (connect(fd, (void*) &aa, sizeof(aa)) < 0) {
        perror("");
        exit(1);
    }
    char buf[1024];
    fgets(buf, sizeof(buf), stdin);
    write(fd, buf, strlen(buf));
    char c;
    while (read(fd, &c, 1) == 1) {
        putchar(c);
    }
    close(fd);
}
