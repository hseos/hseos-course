#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>

int main()
{
    int fd = open("fifo", O_WRONLY);
    FILE *out = fdopen(fd, "w");
    setbuf(out, NULL);
    int c;
    while ((c = getchar()) != EOF) {
        putc(c, out);
    }
    fclose(out);
}
