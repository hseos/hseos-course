#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char *argv[], char *envp[])
{
    int pid = fork();
    if (pid < 0) {
        fprintf(stderr, "Fork: %s\n", strerror(errno));
        exit(1);
    } else if (!pid) {
        chdir("/tmp");
        int fd = open("mylog.txt", O_WRONLY | O_CREAT | O_TRUNC, 0600);
        dup2(fd, 1); close(fd);
        execlp("sh", "sh", "-c", argv[1], NULL);
        fprintf(stderr, "Exec: %s\n", strerror(errno));
        _exit(1);
    } else {
        wait(NULL);
    }
}

