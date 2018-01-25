        .data
A:      .int    0
B:      .int    0
C:      .int    0

        .text
        .global main

        // позиционно-независимая работа с глобальными переменными
main:
        push    %ebx
        call    L1
L1:     pop     %ebx
        // в регистре %ebx - абсолютный адрес по которому размещается L1
        lea     B - L1(%ebx), %eax
        // в %eax - абсолютный адрес B
        push    %eax
        lea     A - L1(%ebx), %eax
        push    %eax
        lea     str1 - L1(%ebx), %eax
        push    %eax
        call    scanf
        add     $12, %esp

        mov     A - L1(%ebx), %eax
        add     B - L1(%ebx), %eax
        push    %eax
        lea     str2 - L1(%ebx), %eax
        push    %eax
        call    printf
        add     $8, %esp

        pop     %ebx
        ret
str1:   .asciz  "%d%d"
str2:   .asciz  "%d\n"
