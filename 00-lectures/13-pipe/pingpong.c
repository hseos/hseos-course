#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

void dowork(int infd, int outfd)
{
    while (1) {
        int v;
        read(infd, &v, sizeof(v));
        printf("%d %d\n", getpid(), v);
        ++v;
        write(outfd, &v, sizeof(v));
    }
}

int main(void)
{
    int p1[2];
    int p2[2];

    pipe(p1);
    pipe(p2);
    int v = 1;
    write(p1[1], &v, sizeof(v));
    if (!fork()) {
        close(p1[0]); close(p2[1]);
        dowork(p2[0], p1[1]);
    }
    if (!fork()) {
        close(p1[1]); close(p2[0]);
        dowork(p1[0], p2[1]);
    }
    close(p1[0]); close(p1[1]);
    close(p2[0]); close(p2[1]);
    wait(NULL);
    wait(NULL);
    return 0;
}
