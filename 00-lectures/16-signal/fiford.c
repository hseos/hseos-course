#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>

int main()
{
    int fd = open("fifo", O_RDONLY);
    FILE *in = fdopen(fd, "r");
    int c;
    while ((c = getc(in)) != EOF) {
        putchar(c);
    }
    fclose(in);
}
