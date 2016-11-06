#include <stdio.h>

extern "C" void plugin_init_func(void);

void plugin_init_func(void)
{
    printf("Plugin init\n");
}
