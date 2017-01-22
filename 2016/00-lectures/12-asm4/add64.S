// в этом фрагменте складываются два 64-битных числа
// %esi - &b
// %edi - &a
// a += b
        mov     (%esi), %eax
        add     %eax, (%edi)
        mov     4(%esi), %eax
        adc     %eax, 4(%edi)
