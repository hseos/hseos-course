#include <asm/unistd_32.h>
        .text
        .global _start

str:    .asciz  "Hello!\n"
strend:

_start:
        mov     $__NR_write, %eax
        mov     $1, %ebx
        mov     $str, %ecx
        mov     $strend - str - 1, %edx
        int     $0x80
        
        mov     $__NR_exit, %eax
        xor     %ebx, %ebx
        int     $0x80
