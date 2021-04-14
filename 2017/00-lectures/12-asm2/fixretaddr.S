        .text
        .global main
main:
        mov     var, %eax
        call    writei32
        call    nl
        call    proc
        call    finish
proc:
        movl    $main, (%esp) // адрес возврата заменяется на адрес main
        ret
        .data
var:    .int    100
