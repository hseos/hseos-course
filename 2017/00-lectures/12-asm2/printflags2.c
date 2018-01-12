#include <stdio.h>

/*
 * эта программа выводит значения флагов OF, SF, ZF, CF после 
 * сложения двух 8-битных чисел
 */
int main(void)
{
    int a, b;
    int c, d;
    while (scanf("%d%d", &a, &b) == 2) {
        asm("movl   %2, %%eax\n"
            "movl   %3, %%edx\n"
            "addb   %%dl, %%al\n"
            "pushf\n"
            "popl   %%edx\n"
            "movzbl %%al, %%eax\n"
            "movl   %%eax, %0\n"
            "movl   %%edx, %1\n"
            : "=g" (c), "=g" (d)
            : "g" (a), "g" (b)
            : "eax", "edx");
        printf("%d OF=%d SF=%d ZF=%d CF=%d\n", c, (d >> 11) & 1, (d >> 7) & 1, (d >> 6) & 1, d & 1);
    }
}
