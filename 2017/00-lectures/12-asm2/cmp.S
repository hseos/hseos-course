/*
сравнение двух чисел как знаковых и как беззнаковых
*/
        .text
        .global main
main:
        call    readi32
        mov     %eax, %esi
        call    readi32
        //  %eax = (%eax > %esi)
        cmp     %esi, %eax    // eax - esi
        //ja      L1          // eax > esi - беззнаковое сравнение
        jg      L1            // знаковое сравнение
        mov     $0, %eax
        jmp     L2
L1:     mov     $1, %eax
L2:     call    writei32
        call    nl
        call    finish
