        .text
main:
        // вывести значение, хранящееся в ячейке var
        mov     var, %eax
        call    writei32
        call    nl
        // вывести адрес ячейки var
        mov     $var, %eax
        call    writei32
        call    nl
        call    finish
        .data
var:    .int    100
        .global main
