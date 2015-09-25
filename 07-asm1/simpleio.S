/* -*- asm -*- */

        .extern scanf
        .text
_form1: .asciz  "%d"
        .text
        .align  16
readi32:
        pushl   %ebp
        movl    %esp, %ebp

        subl    $4, %esp
        leal    -4(%ebp), %eax
        pushl   %eax
        pushl   $_form1
        call    scanf
        add     $8, %esp
        movl    %eax, %ecx
        movl    -4(%ebp), %eax
        clc
        cmpl    $1, %ecx
        je      readi32x
        stc
readi32x:       
        movl    %ebp, %esp
        popl    %ebp
        ret

        .extern printf
        .text
_form2: .asciz  "%d"
        .text
        .align  16
writei32:       
        pushl   %ebp
        movl    %esp, %ebp

        pushl   %eax
        pushl   $_form2
        call    printf
        add     $8, %esp

        movl    %ebp, %esp
        popl    %ebp
        ret

        .extern putchar
        .align  16
nl:
        pushl   %ebp
        movl    %esp, %ebp
        pushl   $'\n'
        call    putchar
        movl    %ebp, %esp
        popl    %ebp
        ret

        .text
        .align  16
        .extern exit
finish:
        pushl   $0
        call    exit
