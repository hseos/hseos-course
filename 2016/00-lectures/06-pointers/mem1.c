#include <stdlib.h>
#include <stdio.h>
#include <string.h>

enum { ALLOC_COUNT = 4 * 1024 * 1024 };

/*
в аргументе командной строки задается размер
области данных, которая многократно будет выделяться
в куче
*/
int main(int argc, char *argv[])
{
    int blk = strtol(argv[1], NULL, 10);
    for (int i = 0; i < ALLOC_COUNT; ++i) {
        malloc(blk); // возвращаемое значение проигнорировано
    }
    char buf[1024];
    FILE *f = fopen("/proc/self/status", "r");
    while (fgets(buf, sizeof(buf), f)) {
        if (!strncmp(buf, "VmData:", 7)) {
            printf("%s", buf);
            break;
        }
    }
    fclose(f);
}

