#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int p[2];

    pipe(p);
    if (!fork()) {
        dup2(p[1], 1);
        close(p[0]); close(p[1]);
        execlp("ls", "ls", "/", NULL);
    }
    close(p[1]);
    if (!fork()) {
        dup2(p[0], 0);
        close(p[0]);
        execlp("wc", "wc", NULL);
    }
    close(p[0]);
    wait(NULL);
    wait(NULL);
    return 0;
}
