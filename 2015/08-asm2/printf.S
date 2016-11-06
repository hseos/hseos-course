	.text
msg1:	.asciz	"Hello, %s!\n"
	.align	16
	.global	func
func:
	//	assume we received string in %esi
	//	that is non-standard
	pushl	%esi
	pushl	$msg1
	call	printf
	addl	$8, %esp
	ret
