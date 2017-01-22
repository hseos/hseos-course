        // вычитание двух чисел с помощью FPU
        .global main
        .text
main:
        push    %ebp
        sub     $16, %esp
        sub     $16, %esp
        movl    $L1, (%esp)
        lea     16(%esp), %eax
        mov     %eax, 4(%esp)
        lea     24(%esp), %eax
        mov     %eax, 8(%esp)
        call    scanf
        add     $16, %esp

        fldl    8(%esp)
        fldl    (%esp)
        fsubp   %st(1)

        sub     $16, %esp
        movl    $L2, (%esp)
        fstpl   4(%esp)
        call    printf
        add     $16, %esp
        add     $16, %esp
        pop     %ebp
        ret
L1:     .asciz  "%lf%lf"
L2:     .asciz  "%.10g\n"
        
