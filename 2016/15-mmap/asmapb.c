#include <stdio.h>

int main()
{
    int a, b, c;
    while (scanf("%d%d", &a, &b) == 2) {
        asm("movl %1, %%eax\n"
            "movl %2, %%edx\n"
            "add  %%edx, %%eax\n"
            "movl %%eax, %0"
            : "=g" (c)
            : "g" (a - 3), "g" (b)
            : "%eax", "%edx");
        printf("%d\n", c);
    }
}
