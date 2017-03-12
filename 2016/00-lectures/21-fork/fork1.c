#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("In process:\n"); fflush(NULL);
    int pid1 = fork();
    int pid2 = fork();
    printf("%d %d %d %d\n", pid1, pid2, getpid(), getppid());
    exit(257);
}
