#include <signal.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{

    //signal(SIGINT, SIG_IGN);
   // signal(SIGINT, SIG_DFL);
   // signal(SIGINT, SIG_IGN);

    void * old = signal(SIGINT, SIG_IGN);
    (void) old;

    signal(SIGKILL, SIG_IGN);
    signal(SIGSEGV, SIG_IGN);

    main();

    //signal(SIGINT, old);
    unsigned p;
    scanf("%x", &p);
    *(char*) p = 'a';

    while (1) pause();
}
