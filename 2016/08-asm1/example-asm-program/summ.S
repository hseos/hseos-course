        .data
        .extern N
        .extern A
        .extern B
        .extern R
        .text
        .global summ_asm
        .global summ2_asm
summ_asm:
        movl    N, %ebx
        movl    $0, %eax
        xorl    %eax,%eax  // the same as
                           // in prev line
LoopBegin:
        // if ( !(i<N) )
        // equals: if ( i>=N )
        // for AT&T (gcc/clang) syntax:
        //  cmpl   N, i
        cmpl    %ebx, %eax
        // (J)ump if (G)reat or (E)qual
        jge     LoopEnd

        movl    A, %edx
        // mov Off(Base,Indx,ElemSize)
        //   Addr=Off+Base+Indx*ElemSize
        movl    0(%edx,%eax,4), %esi

        movl    B, %edx
        movl    0(%edx,%eax,4), %edi

        addl    %edi, %esi

        movl    R, %edx
        movl    %esi, 0(%edx,%eax,4)
        
        incl    %eax // ++i;
        jmp     LoopBegin
LoopEnd:
        
        ret

summ2_asm:
        // %ecx has special case:
        //   used by loop instruction
        movl    N, %ecx
Loop2Begin:
        movl    A, %edx
        // mov Off(Base,Indx,ElemSize)
        //   Addr=Off+Base+Indx*ElemSize
        movl    -4(%edx,%ecx,4), %esi

        movl    B, %edx
        movl    -4(%edx,%ecx,4), %edi

        addl    %edi, %esi

        movl    R, %edx
        movl    %esi, -4(%edx,%ecx,4)

        // loop:
        //  - decrements %ecx
        //  - checks it for zero
        //  - if not zero - jumps to label
        loop    Loop2Begin        
        ret
