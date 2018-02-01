#include <asm/unistd_32.h>

        .global _start
_start:

loop:
        mov     $__NR_read, %eax
        mov     $0, %ebx
        mov     $var, %ecx
        mov     $1, %edx
        int     $0x80
        test    %eax, %eax
        jle     out

        mov     $__NR_write, %eax
        mov     $1, %ebx
        int     $0x80
        jmp     loop


out:
        mov     $__NR_exit, %eax
        xor     %ebx, %ebx
        int     $0x80

        .data
var:    .int    0
