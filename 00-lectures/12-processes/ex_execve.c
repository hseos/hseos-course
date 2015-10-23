#include <unistd.h>
#include <string.h>
#include <stdio.h>

extern char **environ;

int main()
{
    char *args[4];
    args[0] = "/bin/env";
    args[1] = NULL;
    char *env[2];
    env[0] = "A=B";
    env[1] = NULL;
    execve("/bin/env", args, env);
    perror("execve");
    return 1;
}
