#include <stdio.h>
#include <unistd.h>
#include <limits.h>

int main()
{
    int p[2];
    char data[PIPE_BUF];
    int count = 0;

    printf("PIPE_BUF: %d\n", PIPE_BUF);

    pipe(p);
    while (1) {
        int w = write(p[1], data, sizeof(data));
        count += w;
        printf("%d %d\n", w, count);
    }
}
