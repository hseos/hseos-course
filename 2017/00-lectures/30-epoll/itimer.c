#include <signal.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

void handler(int s)
{
    printf("Alarmed\n");
}

int main(void)
{
    signal(SIGALRM, handler);
    struct itimerval itv = { .it_interval = { .tv_sec = 2, .tv_usec = 500000 },
.it_value = { .tv_sec = 1 } };
    setitimer(ITIMER_REAL, &itv, NULL);
    //while (1) {} //pause();
    while (1) pause();
}
