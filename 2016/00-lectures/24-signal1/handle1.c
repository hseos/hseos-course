#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handle(int s)
{
    printf("%d\n", s);
/*
    if (s == SIGSEGV)
        pause();
*/
    if (s == SIGSEGV) {
        *(char*) s = 'a';
    }
}

int main()
{
    signal(SIGINT, handle);
    signal(SIGKILL, handle);
    signal(SIGSEGV, handle);
    signal(SIGABRT, SIG_IGN);

    //main();

    unsigned p;
    scanf("%x", &p);
    *(char*) p = 'a';

    while (1) pause();
}
