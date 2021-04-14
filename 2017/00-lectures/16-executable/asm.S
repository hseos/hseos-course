        .text
        .global asmFunc
asmFunc:
        push    %ebx
        call    __x86.get_pc_thunk.bx
L1:
        add     $_GLOBAL_OFFSET_TABLE_, %ebx
        mov     libVar@got(%ebx), %eax
        incl    (%eax)
        //incl    libVar
        incl    mainVar
        pop     %ebx
        ret
