        .data
A:      .int    0
B:      .int    0
C:      .int    0

        .text
        .global main

        // использование подпрограммы __x86.get_pc_thunk.bx
main:
        push    %ebx
        call    __x86.get_pc_thunk.bx
L1:     lea     B - L1(%ebx), %eax
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
