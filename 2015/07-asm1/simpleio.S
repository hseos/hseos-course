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

        .text
_form3: .asciz  "%lld"
        .align  16
readi64:
        pushl   %ebp
        movl    %esp, %ebp

        subl    $8, %esp
        leal    -8(%ebp), %eax
        pushl   %eax
        pushl   $_form3
        call    scanf
        add     $8, %esp
        movl    %eax, %ecx
        movl    -8(%ebp), %eax
        movl    -4(%ebp), %edx
        clc
        cmpl    $1, %ecx
        je      readi64x
        stc
readi64x:       
        movl    %ebp, %esp
        popl    %ebp
        ret

        .text
_form4: .asciz  "%lld"
        .align  16
writei64:       
        pushl   %ebp
        movl    %esp, %ebp

        pushl   %edx
        pushl   %eax
        pushl   $_form4
        call    printf
        add     $12, %esp

        movl    %ebp, %esp
        popl    %ebp
        ret
