#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

/*
 * неблокирующее чтение из файла
 */

int main(int argc, char *argv[])
{
    int count = 0;
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    // переключаем файловый дескриптор в неблокирующий режим
    fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK);

    while (1) {
        char c;
        int r = read(fd, &c, 1);
        if (r < 0 && errno == EAGAIN) {
            printf("waiting %d\r", ++count);
        } else if (!r) {
            break;
        } else {
            write(1, &c, 1);
        }
    }
}
