#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

double A, B, C;

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "wrong number of args\n");
        return 1;
    }
    void *handle = dlopen(argv[1], RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "failed to load SO: %s\n", dlerror());
        return 1;
    }
    void *func = dlsym(handle, "process");
    if (!func) {
        fprintf(stderr, "failed to find 'process' symbol: %s\n", dlerror());
        return 1;
    }
    while (scanf("%lf%lf", &A, &B) == 2) {
        ((void (*)(void)) func)();
        printf("%.13g\n", C);
    }
    return 0;
}
