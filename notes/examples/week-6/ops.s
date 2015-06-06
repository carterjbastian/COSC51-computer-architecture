	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 10
	.globl	_arith
	.align	4, 0x90
_arith:                                 ## @arith
## BB#0:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$28, %esp
	movl	16(%ebp), %eax
	movl	12(%ebp), %ecx
	movl	8(%ebp), %edx
	movl	%edx, -4(%ebp)
	movl	%ecx, -8(%ebp)
	movl	%eax, -12(%ebp)
	movl	-4(%ebp), %eax
	addl	-8(%ebp), %eax
	movl	%eax, -16(%ebp)
	imull	$48, -12(%ebp), %eax
	movl	%eax, -20(%ebp)
	movl	-16(%ebp), %eax
	andl	$65535, %eax            ## imm = 0xFFFF
	movl	%eax, -24(%ebp)
	movl	-20(%ebp), %eax
	imull	-24(%ebp), %eax
	movl	%eax, -28(%ebp)
	movl	-28(%ebp), %eax
	addl	$28, %esp
	popl	%ebp
	retl


.subsections_via_symbols
