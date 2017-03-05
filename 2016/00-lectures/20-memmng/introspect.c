#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

void myfunc(int z)
{
    printf("myfunc: %d\n", z);
}

int main()
{
    void *handle = dlopen(NULL, RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "1\n");
        abort();
    }
    void *func = dlsym(handle, "myfunc");
    if (!func) {
        fprintf(stderr, "2\n");
        abort();
    }
    ((void (*)(int)) func)(1234);
}
