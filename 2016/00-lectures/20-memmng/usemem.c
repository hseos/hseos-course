#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_status(void)
{
    FILE *f = fopen("/proc/self/status", "r");
    if (!f) abort();
    char buf[1024];
    while (fgets(buf, sizeof(buf), f)) {
        if (buf[0] == 'V' && buf[1] == 'm') {
            fputs(buf, stdout);
        }
    }
    fclose(f);
}

int main(int argc, char *argv[])
{
    int zm = strtol(argv[1], NULL, 10);
    print_status();
    printf("Waiting for enter"); fflush(stdout); getchar();
    size_t zz = zm * 1024 * 1024;
    printf("Allocating %zu bytes\n", zz);
    char *ptr = malloc(zz);
    if (!ptr) {
        printf("Failed\n");
        exit(0);
    }
    printf("Success: %p\n", ptr);
    print_status();
    printf("Waiting for enter"); fflush(stdout); getchar();
    printf("Filling up memory\n");
    memset(ptr, -1, zz);
    printf("Success\n");
    print_status();
    printf("Waiting for enter"); fflush(stdout); getchar();
}
