#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int counter = 5;

void alrmhnd(int s)
{
    if (!--counter) {
        kill(getpid(), SIGTERM);
    }
    alarm(1);
    char buf[64];
    snprintf(buf, sizeof(buf), "Remained %d\n", counter); 
    write(1, buf, strlen(buf));
}

int main()
{
    int sum = 0, x;
    signal(SIGALRM, alrmhnd);
    alarm(1);
    while (scanf("%d", &x) == 1) {
        sum += x;
    }
    printf("%d\n", sum);
}
