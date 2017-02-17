#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

extern char process[], end_process[];

int main(void)
{
    size_t size = end_process - process;
    if (size < 10 || size > 1024) {
        fprintf(stderr, "invalid code size: %zu\n", size);
        return 1;
    }
    char *ptr = malloc(size + 8);
    if (!ptr) {
        fprintf(stderr, "malloc failed\n");
        return 1;
    }
    size_t len = strnlen(process, size);
    memcpy(ptr + 8, process, len);

    unsigned long addr1 = (unsigned long) process;
    unsigned long addr2 = (unsigned long) end_process;
    addr1 = addr1 & -4096;
    addr2 = (addr2 + 4095) & -4096;
    mprotect((void*) addr1, addr2 - addr1, PROT_READ | PROT_WRITE | PROT_EXEC);
    *((void**) process) = NULL;
    *((void**) process + 1) = NULL;
    memset(process, 0, size);

    *((void**) ptr) = scanf;
    *((void**) ptr + 1) = printf;
    ((void (*)(void)) (ptr + 8))();
}
