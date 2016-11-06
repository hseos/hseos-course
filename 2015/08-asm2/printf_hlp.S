#define SIZE 1024
	.text
	.global main
main:
	pushl	$buf
	call	gets
	addl	$4, %esp
	movl	$buf, %esi
	call	func
	xorl	%eax, %eax
	ret


	.data
buf:	.space	SIZE, 0
