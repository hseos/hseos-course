#include <stdio.h>

unsigned char arg1, arg2, res;
unsigned flg;

void byteadd(void);

int main(void)
{
    int x, y;
    while (scanf("%d%d", &x, &y) == 2) {
        arg1 = x;
        arg2 = y;
        byteadd();
        printf("%d(%d) + %d(%d) = %d(%d), ZF=%d, SF=%d, CF=%d, OF=%d\n",
                arg1, (signed char) arg1,
                arg2, (signed char) arg2,
                res, (signed char) res,
                (flg >> 6) & 1,
                (flg >> 7) & 1,
                flg & 1,
                (flg >> 11) & 1);
    }
}
