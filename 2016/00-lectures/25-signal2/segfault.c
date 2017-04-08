#include <signal.h>
#include <stdio.h>

int main()
{
    sigset_t ss;
    sigfillset(&ss);
    sigprocmask(SIG_BLOCK, &ss, NULL);

    int x;
    scanf("%d", &x);
    *(int *) x = 0;
}
