	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 10
	.globl	_exchange
	.align	4, 0x90
_exchange:                              ## @exchange
## BB#0:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$12, %esp
	movl	12(%ebp), %eax
	movl	8(%ebp), %ecx
	movl	%ecx, -4(%ebp)
	movl	%eax, -8(%ebp)
	movl	-4(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, -12(%ebp)
	movl	-8(%ebp), %eax
	movl	-4(%ebp), %ecx
	movl	%eax, (%ecx)
	movl	-12(%ebp), %eax
	addl	$12, %esp
	popl	%ebp
	retl


.subsections_via_symbols
