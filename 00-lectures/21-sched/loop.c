#include <stdio.h>
#include <sched.h>

int main()
{
    int serial = 0;
    int pid = getpid();
    while (1) {
        printf("%d %d\n", pid, ++serial);
        sched_yield();
    }
}
