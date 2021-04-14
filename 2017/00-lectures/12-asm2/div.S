/*
считать два числа a и b и вывести частное и остаток
*/
        .text
        .global main
main:   call    readi32
        mov     %eax, %ebx
        call    readi32
        xchg    %eax, %ebx   // меняем местами %eax и %ebx
        xor     %edx, %edx   // очищаем %edx
        idiv    %ebx         // в результате: %eax - частное, %edx - остаток
        mov     %edx, %ebx   // сохраняем %edx, чтобы не потерять
        call    writei32
        call    nl
        mov     %ebx, %eax
        call    writei32
        call    nl
        call    finish
