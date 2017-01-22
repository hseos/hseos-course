// один из вариантов генерации кода
// while (*dst++ = *src++) {}
// dst - %edi
// src - %esi
.L1:
        mov     (%esi), %al
        tst     %al, %al
        mov     %al, (%edi)
        lea     1(%esi), %esi
        lea     1(%edi), %edi
        jnz     .L1
