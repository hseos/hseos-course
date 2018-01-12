        .text
        .global main
main:   call    readi32
        mov     %eax,%ebx
        call    readi32
        imul    %ebx      // получаем 64-битный результат в edx:eax
        call    writei64
        call    nl
        call    finish
