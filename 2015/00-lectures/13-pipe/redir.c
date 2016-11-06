#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>

int main()
{
    if (!fork()) {
        int fd = open("out.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
        dup2(fd, 1); close(fd);
        execlp("ls", "ls", "-l", "/", NULL);
        exit(1);
    }

    wait(NULL);
}
