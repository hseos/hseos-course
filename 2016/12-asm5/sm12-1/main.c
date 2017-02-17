#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char process[], scanp[], printp[], end_process[];

int main(void)
{
    size_t size = end_process - process;
    if (size < 10 || size > 1024) {
        fprintf(stderr, "invalid code size: %zu\n", size);
        return 1;
    }
    char *ptr = malloc(size);
    if (!ptr) {
        fprintf(stderr, "malloc failed\n");
        return 1;
    }
    memcpy(ptr, process, size);
    memset(process, 0, size);

    // scanf fixup
    char *newscanp = ptr + (scanp - process);
    unsigned offset = (char*) scanf - (newscanp + 5);
    *((unsigned*) (newscanp + 1)) = offset;

    // printf fixup
    char *newprintp = ptr + (printp - process);
    offset = (char*) printf - (newprintp + 5);
    *((unsigned*) (newprintp + 1)) = offset;

    ((void (*)(void)) ptr)();
}
