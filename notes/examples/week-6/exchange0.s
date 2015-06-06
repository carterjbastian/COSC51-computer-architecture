	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 10
	.globl	_exchange0
	.align	4, 0x90
_exchange0:                             ## @exchange0
## BB#0:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	calll	L0$pb
L0$pb:
	popl	%eax
	movl	L_xp$non_lazy_ptr-L0$pb(%eax), %ecx
	movl	(%ecx), %ecx
	movl	(%ecx), %edx
	movl	L_x$non_lazy_ptr-L0$pb(%eax), %esi
	movl	%edx, (%esi)
	movl	L_y$non_lazy_ptr-L0$pb(%eax), %eax
	movl	(%eax), %eax
	movl	%eax, (%ecx)
	popl	%esi
	popl	%ebp
	retl

	.comm	_xp,4,2                 ## @xp
	.comm	_x,4,2                  ## @x
	.comm	_y,4,2                  ## @y

	.section	__IMPORT,__pointers,non_lazy_symbol_pointers
L_x$non_lazy_ptr:
	.indirect_symbol	_x
	.long	0
L_xp$non_lazy_ptr:
	.indirect_symbol	_xp
	.long	0
L_y$non_lazy_ptr:
	.indirect_symbol	_y
	.long	0

.subsections_via_symbols
