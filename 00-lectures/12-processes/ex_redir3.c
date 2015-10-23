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
        int fd = open("log.txt", O_WRONLY | O_CREAT | O_APPEND, 0600);
        dup2(fd, 2);
        close(fd);
        execlp("/bin/ls", "/bin/ls", "-l", "/sss", NULL);
        exit(1);
    }
    wait(NULL);
    return 0;
}
