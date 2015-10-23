#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(void)
{
    printf("before: %d, %d\n", getuid(), geteuid());
    int fd = open("safefile", O_RDONLY, 0);
    if (fd < 0) perror("open1");
    if (setuid(1000) < 0) perror("seteuid");
    printf("after: %d, %d\n", getuid(), geteuid());
    fd = open("safefile", O_RDONLY, 0);
    if (fd < 0) perror("open2");
    if (seteuid(0) < 0) perror("seteuid2");
    printf("after: %d, %d\n", getuid(), geteuid());
    return 0;
}
