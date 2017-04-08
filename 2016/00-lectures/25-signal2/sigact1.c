#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void handler(int s)
{
    printf("SIGINT\n");
    pause();
    printf("DONE\n");
}

int main()
{
    struct sigaction act =
    {
        .sa_handler = handler,
        .sa_flags = SA_NODEFER
    };
    sigaction(SIGINT, &act, NULL);
    while (1) pause();
}
