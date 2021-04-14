#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[], char *envp[])
{
    int pid = fork();
    if (pid < 0) {
        fprintf(stderr, "Fork: %s\n", strerror(errno));
        exit(1);
    } else if (!pid) {
        execlp("sh", "sh", "-c", argv[1], NULL);
        fprintf(stderr, "Exec: %s\n", strerror(errno));
        _exit(1);
    } else {
        wait(NULL);
    }
}

