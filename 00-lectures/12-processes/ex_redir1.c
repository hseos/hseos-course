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
        int fd = open("result.txt", O_WRONLY | O_CREAT | O_TRUNC, 0600);
        dup2(fd, 1);
        close(fd);
        execlp("/bin/ls", "/bin/ls", "-l", "/", NULL);
        exit(1);
    }
    wait(NULL);
    return 0;
}
