#include <stdio.h>
#include <signal.h>

// блокировка и разблокировка сигналов

void handler(int s)
{
    printf("signal %d\n", s);
}

int main()
{
    sigset_t s1 = {}, s2;
    sigaction(SIGINT,
            &(struct sigaction) { .sa_handler = handler,
                                    .sa_flags = SA_RESTART }, NULL);

    sigemptyset(&s1);
    sigaddset(&s1, SIGINT);

    int x;
    while (scanf("%d", &x) == 1) {
        if (x == 10) {
            sigprocmask(SIG_BLOCK, &s1, &s2);
        } else if (x == 11) {
            sigprocmask(SIG_SETMASK, &s2, NULL);
        }
        printf("%d\n", x);
    }
}
