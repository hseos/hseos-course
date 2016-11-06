#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sched.h>

void dowork(int infd, int outfd)
{
    while (1) {
        int v;
        read(infd, &v, sizeof(v));
        printf("%d %d\n", getpid(), v);
        ++v;
        write(outfd, &v, sizeof(v));
        sched_yield();
    }
}

int main(void)
{
    int p1[2];

    pipe(p1);
    int v = 1;
    write(p1[1], &v, sizeof(v));
    if (!fork()) {
        dowork(p1[0], p1[1]);
    }
    if (!fork()) {
        dowork(p1[0], p1[1]);
    }
    close(p1[0]); close(p1[1]);
    wait(NULL);
    wait(NULL);
    return 0;
}
