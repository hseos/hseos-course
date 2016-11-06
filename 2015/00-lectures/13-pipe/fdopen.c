#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int p[2];

    pipe(p);
    if (!fork()) {
        dup2(p[0], 0); close(p[0]); close(p[1]);
        execlp("cat", "cat", NULL);
    }

    close(p[0]);

    FILE *ff = fdopen(p[1], "w");
    fprintf(ff, "1\n"); fflush(ff);
    sleep(1);
    fprintf(ff, "2\n"); fflush(ff);
    sleep(1);
    fprintf(ff, "3\n");
    fclose(ff);
    wait(NULL);
}
