// вывести адрес, по которому размещается программа
        .text
main:
        call    L1  // в стек помещается адрес следующей инструкции
L1:
        pop     %eax // адрес этой инструкции помещается в eax
        call    writei32
        call    nl
        call    finish
        .global main
