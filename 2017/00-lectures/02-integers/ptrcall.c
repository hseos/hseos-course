#include <stdio.h>

// Undefined behavior (UB) при разыменовании 
// компилируйте clang, сравните вывод оптимизированной и неоптимизированной программ
typedef void (*myfunc_t)(void);

static myfunc_t func;

void redalert(void)
{
    printf("RED ALERT!\n");
}

void setfunc2()
{
    func = redalert;
}

int main()
{
    func();
}
