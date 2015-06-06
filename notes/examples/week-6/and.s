	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 10
	.globl	_ander
	.align	4, 0x90
_ander:                                 ## @ander
## BB#0:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	calll	L0$pb
L0$pb:
	popl	%eax
	movl	12(%ebp), %ecx
	movl	8(%ebp), %edx
	movzwl	%dx, %esi
	movl	L_t1$non_lazy_ptr-L0$pb(%eax), %edi
	movl	%esi, (%edi)
	movl	%ecx, %esi
	andl	%edx, %esi
	movl	L_t2$non_lazy_ptr-L0$pb(%eax), %edi
	movl	%esi, (%edi)
	testl	%ecx, %ecx
	setne	%cl
	testl	%edx, %edx
	setne	%dl
	andb	%cl, %dl
	movzbl	%dl, %ecx
	movl	L_t3$non_lazy_ptr-L0$pb(%eax), %eax
	movl	%ecx, (%eax)
	popl	%esi
	popl	%edi
	popl	%ebp
	retl

	.comm	_t1,4,2                 ## @t1
	.comm	_t2,4,2                 ## @t2
	.comm	_t3,4,2                 ## @t3
	.comm	_t4,4,2                 ## @t4

	.section	__IMPORT,__pointers,non_lazy_symbol_pointers
L_t1$non_lazy_ptr:
	.indirect_symbol	_t1
	.long	0
L_t2$non_lazy_ptr:
	.indirect_symbol	_t2
	.long	0
L_t3$non_lazy_ptr:
	.indirect_symbol	_t3
	.long	0

.subsections_via_symbols
