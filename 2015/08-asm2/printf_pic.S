	.text
msg1:	.asciz	"Hello, %s!\n"
	.align	16
	.global	func
func:
	//	assume we received string in %esi
	//	that is non-standard
	pushl	%esi
	call	l1
l1:	popl	%eax
	addl	$msg1 - l1, %eax
	pushl	%eax
	call	printf
	addl	$8, %esp
	ret
