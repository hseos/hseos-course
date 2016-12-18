    .text
    .global byteadd
    .extern arg1
byteadd:
    movb    arg1, %al
    movb    arg2, %cl
    addb    %cl, %al
    pushf
    movb    %al, res
    pop     flg
    ret
