#include <stdio.h>

extern int var1;
extern char var2[];
extern char var3[];

int main(void)
{
    printf("%d\n%s\n%s\n", var1, var2, var3);
}
