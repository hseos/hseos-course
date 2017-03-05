#include <stdio.h>
#include <dlfcn.h>

void func2(void)
{
    printf("func2\n");
}

int main(void)
{
    void *handle = dlopen("./sofile.so", RTLD_LAZY);
    void *func = dlsym(handle, "myfunc");
    ((int (*)()) func)(234);
}
