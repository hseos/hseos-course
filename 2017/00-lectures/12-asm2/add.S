/*
если сумма двух 32-битных знаковых чисел чисел
непредставима 32-битным знаковым числом, печатается 0 
*/
        .text
        .global main
main:
        call    readi32
        mov     %eax, %esi
        call    readi32
        // __builtin_add_overflow
        add     %esi, %eax
        jno     L2
        mov     $0, %eax
L2:     call    writei32
        call    nl
        call    finish
