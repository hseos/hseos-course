#include <stdio.h>
#include <float.h>

// программа выводит машинный эпсилон (то есть ULP в точке 1.0)
// для трех типов с плавающей точкой
// спецификатор %a выводит вещественное число в шестнадцатеричном виде,
// то есть гарантируется сохранение всех бит числа
int main()
{
    printf("%g %a\n", FLT_EPSILON, FLT_EPSILON);
    printf("%g %a\n", DBL_EPSILON, DBL_EPSILON);
    printf("%Lg %La\n", LDBL_EPSILON, LDBL_EPSILON);
}
