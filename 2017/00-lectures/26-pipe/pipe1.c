#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <limits.h>

int main()
{
    int pfd[2];

    signal(SIGPIPE, SIG_IGN);
    printf("%d\n", PIPE_BUF);

    pipe(pfd);
    close(pfd[0]);
    size_t sz = 0;
    while (1) {
        char c = '0';
        int r = write(pfd[1], &c, sizeof(c));
        if (r < 0) {
            perror("");
            exit(0);
        }
        printf("%zu\n", ++sz);
    }
}
