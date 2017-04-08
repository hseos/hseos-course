#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void handler(int s)
{
    printf("SIGINT\n");
    printf("DONE\n");
}

int main()
{
    struct sigaction act =
    {
        .sa_handler = handler,
        .sa_flags = SA_RESTART
    };
    sigaction(SIGINT, &act, NULL);
    //char buf[128];
    while (1) {
        //int r = read(0, buf, sizeof(buf));
        int r = sleep(1000);
        if (r < 0) perror("");
        printf("%d\n", r);
    }
}
