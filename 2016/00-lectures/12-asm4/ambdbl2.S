        .global main
        .text
main:
        push    %ebp
        // резервируем 16 байт под два double + 8 под выравнивание
        sub     $24, %esp
        // вызов scanf для чтения двух double
        sub     $16, %esp
        movl    $L1, (%esp)
        lea     16(%esp), %eax
        mov     %eax, 4(%esp)
        lea     24(%esp), %eax
        mov     %eax, 8(%esp)
        call    scanf
        add     $16, %esp

        // вычитание
        movlpd  (%esp), %xmm0
        movlpd  8(%esp), %xmm1
        subpd   %xmm1, %xmm0

        // вывод
        sub     $16, %esp
        movl    $L2, (%esp)
        movlpd  %xmm0, 4(%esp)
        call    printf
        add     $16, %esp

        add     $24, %esp
        pop     %ebp
        ret
L1:     .asciz  "%lf%lf"
L2:     .asciz  "%.10g\n"
        
