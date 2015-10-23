#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(void)
{
    printf("before: %d, %d\n", getuid(), geteuid());
    if (seteuid(1000) < 0) perror("seteuid");
    printf("after: %d, %d\n", getuid(), geteuid());
    if (seteuid(1001) < 0) perror("seteuid2");
    printf("after: %d, %d\n", getuid(), geteuid());
    return 0;
}
