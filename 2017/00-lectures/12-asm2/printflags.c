#include <stdio.h>

/*
 * эта программа выводит значения флагов OF, SF, ZF, CF после 
 * сложения двух 32-битных чисел
 */
int main(void)
{
    int a, b, c, d;
    while (scanf("%d%d", &a, &b) == 2) {
        asm("movl   %2, %%eax\n"
            "addl   %3, %%eax\n"
            "pushf\n"
            "popl   %%edx\n"
            "movl   %%eax, %0\n"
            "movl   %%edx, %1\n"
            : "=g" (c), "=g" (d)
            : "g" (a), "g" (b)
            : "eax", "edx");
        printf("%d OF=%d SF=%d ZF=%d CF=%d\n", c, (d >> 11) & 1, (d >> 7) & 1, (d >> 6) & 1, d & 1);
    }
}
