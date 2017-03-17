#include <stdio.h>
#include <unistd.h>

extern char **environ;
int main(int argc, char *argv[])
{
    char *args[] = { argv[1], NULL, "1", "2", "3", NULL };
    char *envs[] = { "VAR1=VAL1", "VAR2=VAL2", NULL };

    execve(argv[1], args, environ);
    perror("execve");
}
