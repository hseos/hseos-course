#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(void)
{
    int pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    }
    if (!pid) {
        chdir("/");
        execlp("/bin/ls", "/bin/ls", "-l", ".", NULL);
        perror("execlp");
        exit(1);
    }
    wait(NULL);
}
