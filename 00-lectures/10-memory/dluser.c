#include <dlfcn.h>
#include <stdio.h>

typedef void (*func_ptr_t)(void);

int main(void)
{
    void *dl = dlopen("./dllib2.so", RTLD_LAZY);
    void *sym = dlsym(dl, "plugin_init_func");
    //void *sym = dlsym(dl, "_Z16plugin_init_funcv");
    ((func_ptr_t) sym)();
    getchar();
    dlclose(dl);
}
