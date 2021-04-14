#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


void func(int rfd, int wfd)
{
    while (1) {
        int x;
        read(rfd, &x, sizeof(x));
        ++x;
        printf("%d %d\n", getpid(), x - 1); fflush(stdout);
        write(wfd, &x, sizeof(x));
    }
}

int main()
{
    int pfd1[2];
    int pfd2[2];
    pipe(pfd1);
    pipe(pfd2);

    {
        int z = 100500;
        write(pfd1[1], &z, sizeof(z));
    }

    int pid1 = fork();
    if (!pid1) {
        func(pfd1[0], pfd2[1]);
        _exit(1);
    }
    int pid2 = fork();
    if (!pid2) {
        func(pfd2[0], pfd1[1]);
        _exit(1);
    }

    wait(NULL);
    wait(NULL);
}
