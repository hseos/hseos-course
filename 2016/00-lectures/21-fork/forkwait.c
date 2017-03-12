#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    int pid3;
    for (int i = 0; i < 5; ++i) {
        pid_t pid = fork();
        if (pid < 0) {
            abort();
        }
        if (!pid) {
            printf("Son %d\n", getpid());
            if (i == 3) abort();
            _exit(i);
        }
        if (i == 3) pid3 = pid;
    }
    int status;
    pid_t pid;
    pid = waitpid(pid3, &status, 0);
    usleep(100000000);
    while ((pid = wait(&status)) > 0) {
        printf("Completed %d %d %d %d %d\n", pid, WIFEXITED(status), WIFSIGNALED(status), WEXITSTATUS(status), WTERMSIG(status));
    }
    printf("Completed\n");
}
