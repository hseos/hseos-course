        .text
        .global main
        // пример на сложение двух 64-битных чисел
main:
        // складываем младшие 32 бита
        mov     A, %eax
        add     B, %eax

        // складываем старшие 32 бита с учетом переноса
        mov     A + 4, %edx
        adc     B + 4, %edx 

        // печатаем результат
        push    %edx
        push    %eax
        pushl   $str
        call    printf
        add     $12, %esp

        // обнуляем возвращаемое значение
        xor     %eax, %eax
        ret

        .data
A:      .quad   -4000000000
B:      .quad   4000000000
str:    .asciz  "%lld\n"
