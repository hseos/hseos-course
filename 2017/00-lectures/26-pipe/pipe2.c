#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

// argv[1] | argv[2]
int main(int argc, char *argv[])
{
    int pfd[2];
    pipe(pfd);

    int pid1 = fork();
    if (!pid1) {
        dup2(pfd[1], STDOUT_FILENO);
        close(pfd[1]);
        close(pfd[0]);
        execlp(argv[1], argv[1], NULL);
        _exit(1);
    }

    close(pfd[1]);
    int pid2 = fork();
    if (!pid2) {
        dup2(pfd[0], STDIN_FILENO);
        close(pfd[0]);
        execlp(argv[2], argv[2], NULL);
        _exit(1);
    }

    close(pfd[0]);
    wait(NULL);
    wait(NULL);
}
