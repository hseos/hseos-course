#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int fd = open(argv[1], O_RDONLY);
    char c;
    while (read(fd, &c, 1) == 1) {
        write(1, &c, 1);
    }
}
