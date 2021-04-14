#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    // setbuf, setvbuf
    printf("Hello"); //fflush(stdout);
    int pid;
    for (int i = 0; i < 10; ++i) {
    pid = fork();
    if (pid < 0) {
        // error
        abort();
    } else if (!pid) {
        if (i < 5) {
            _exit(i);
        } else {
            raise(SIGRTMIN + i);
        }
    }
    }

    sleep(1000);

    // parent
    int pid2;
    int status;
    while ((pid2 = wait(&status)) > 0) {
        printf("process: %d ended: %d", pid, pid2);
        //WIFEXITED(status) && !WEXITSTATUS(status)
        if (WIFEXITED(status)) {
            printf(" exited %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf(" terminated %d\n", WTERMSIG(status));
        }
    }
}
