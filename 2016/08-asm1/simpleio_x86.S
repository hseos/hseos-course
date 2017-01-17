/* -*- asm -*- */

        .text
_form1: .asciz  "%d"
        .text
        .align  16
	.global	readi32
readi32:
        pushl   %ebp
        movl    %esp, %ebp

        subl    $16, %esp
        leal    -4(%ebp), %eax

        pushl   %eax
        pushl   $_form1
#ifdef __APPLE__
        call    _scanf
#else
        call    scanf
#endif
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

        .text
_form2: .asciz  "%d"
        .text
        .align  16
    	.global	writei32
writei32:       
        pushl   %ebp
        movl    %esp, %ebp

        pushl   %eax
        pushl   $_form2
#ifdef __APPLE__
        call    _printf
#else
        call    printf
#endif

        movl    %ebp, %esp
        popl    %ebp
        ret

        .align  16
        .global	nl
nl:
        pushl   %ebp
        movl    %esp, %ebp
        push    %eax            // 16-byte alignment
        pushl   $'\n'
#ifdef __APPLE__
        call    _putchar
#else
        call    putchar
#endif
        movl    %ebp, %esp
        popl    %ebp
        ret

        .text
        .align  16
        .global finish
finish:
        push    %eax            // 16-byte alignment
        push    %eax
        pushl   $0
#ifdef __APPLE__
        call    _exit
#else
        call    exit
#endif

        .text
_form3: .asciz  "%lld"
        .align  16
        .global	readi64
readi64:
        pushl   %ebp
        movl    %esp, %ebp

        subl    $16, %esp
        leal    -8(%ebp), %eax
        sub     $8, %esp
        pushl   %eax
        pushl   $_form3
#ifdef __APPLE__
        call    _scanf
#else
        call    scanf
#endif
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
        .global	writei64
writei64:       
        pushl   %ebp
        movl    %esp, %ebp

        sub     $12, %esp
        pushl   %edx
        pushl   %eax
        pushl   $_form4
#ifdef __APPLE__
        call    _printf
#else
        call    printf
#endif

        movl    %ebp, %esp
        popl    %ebp
        ret
