#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main()
{
    int pid = fork();
    if (!pid) {
        int fd = open("out2.txt", O_WRONLY | O_CREAT | O_TRUNC, 0600);
        dup2(fd, 1); close(fd);
        execlp("/bin/ls", "/bin/ls", "-l", NULL);
        _exit(1);
    }
    wait(NULL);
}
