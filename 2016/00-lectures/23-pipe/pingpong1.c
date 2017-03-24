#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void doson(int n, int fdr, int fdw)
{
    signal(SIGPIPE, SIG_IGN);
    //setbuf(stdout, NULL);
    while (1) {
        int x = 0;
        int z = read(fdr, &x, sizeof(x));
        //printf("z: %d\n", z);
        if (!z) exit(0);
        printf("%d %d\n", n, x); fflush(stdout);
        ++x;
        if (x == 666) exit(0);
        write(fdw, &x, sizeof(x));
    }
}

int main()
{
    int fd1[2];
    int fd2[2];
    pipe(fd1);
    pipe(fd2);

    if (!fork()) {
        close(fd1[1]); close(fd2[0]);
        doson(0, fd1[0], fd2[1]);
    }
    if (!fork()) {
        close(fd1[0]); close(fd2[1]);
        doson(1, fd2[0], fd1[1]);
    }
    int x = 1;
    write(fd1[1], &x, sizeof(x));
    close(fd1[1]); close(fd2[0]);
    close(fd1[0]); close(fd2[1]);
    wait(NULL); wait(NULL);
}
