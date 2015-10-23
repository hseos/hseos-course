#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void)
{
    int pid = fork();
    if (pid == 0) {
        int fd = open("result.txt", O_RDONLY, 0);
        dup2(fd, 0);
        close(fd);
        execlp("/bin/wc", "/bin/wc", "-l", NULL);
        exit(1);
    }
    wait(NULL);
    return 0;
}
