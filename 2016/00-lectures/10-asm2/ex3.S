    .text
    .global dowork
    .extern var1
    .extern doread
    .extern dowrite
dowork:
    call    doread
    xor     %esi, %esi
L1:
    mov     %esi, var2
    call    dowrite
    inc     %esi
    cmp     %esi, var1
    jg      L1
    

    ret

    .data
    .global var2
var2:   .int 0
