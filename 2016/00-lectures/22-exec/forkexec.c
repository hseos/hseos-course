#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int pid = fork();
    if (!pid) {
        execlp("/bin/ls", "/bin/ls", "-l", NULL);
        _exit(1);
    }
    wait(NULL);
}
