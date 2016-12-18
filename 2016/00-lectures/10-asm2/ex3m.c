#include <stdio.h>

int var1;
void doread(void)
{
    scanf("%d", &var1);
}

extern int var2;
void dowrite(void)
{
    printf("%d\n", var2);
}

void dowork(void);

int main(void)
{
    dowork();
}
