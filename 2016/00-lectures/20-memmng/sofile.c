#include <stdio.h>

void func2(void);

int myfunc(int z)
{
    printf("myfunc: %d\n", z);
    func2();
    return z;
}
