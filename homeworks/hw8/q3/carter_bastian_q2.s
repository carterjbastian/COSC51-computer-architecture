	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 10
	.globl	_error_out
	.align	4, 0x90
_error_out:                             ## @error_out
## BB#0:
	pushl	%ebp
	movl	%esp, %ebp
	calll	L0$pb
L0$pb:
	popl	%eax
	movl	L_output$non_lazy_ptr-L0$pb(%eax), %eax
	movl	$14, (%eax)
	popl	%ebp
	retl

	.globl	_get_month
	.align	4, 0x90
_get_month:                             ## @get_month
## BB#0:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movzbl	8(%ebp), %eax
	cmpl	$9, %eax
	ja	LBB1_2
## BB#1:
	movzbl	12(%ebp), %ecx
	cmpl	$10, %ecx
	jae	LBB1_2
## BB#3:
	movzbl	%al, %eax
	imull	 $10, %eax
	addl	%ecx, %eax
	jmp	LBB1_4
LBB1_2:
	calll	_error_out
	movl	$-1, %eax
LBB1_4:
	addl	$8, %esp
	popl	%ebp
	retl

	.globl	_get_day
	.align	4, 0x90
_get_day:                               ## @get_day
## BB#0:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movzbl	8(%ebp), %eax
	cmpl	$9, %eax
	ja	LBB2_2
## BB#1:
	movzbl	12(%ebp), %ecx
	cmpl	$10, %ecx
	jae	LBB2_2
## BB#3:
	movzbl	%al, %eax
	imull	 $10, %eax
	addl	%ecx, %eax
	jmp	LBB2_4
LBB2_2:
	calll	_error_out
	movl	$-1, %eax
LBB2_4:
	addl	$8, %esp
	popl	%ebp
	retl

	.globl	_check_day
	.align	4, 0x90
_check_day:                             ## @check_day
## BB#0:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %edx
	xorl	%eax, %eax
	testl	%edx, %edx
	je	LBB3_10
## BB#1:
	movl	12(%ebp), %ecx
	testl	%ecx, %ecx
	je	LBB3_10
## BB#2:
	cmpl	$12, %edx
	jg	LBB3_10
## BB#3:
	cmpl	$31, %ecx
	jg	LBB3_10
## BB#4:
	decl	%edx
	cmpl	$11, %edx
	ja	LBB3_10
## BB#5:
	calll	L3$pb
L3$pb:
	popl	%eax
Ltmp0 = LJTI3_0-L3$pb
	addl	Ltmp0(%eax,%edx,4), %eax
	jmpl	*%eax
LBB3_8:
	cmpl	$32, %ecx
	jmp	LBB3_9
LBB3_7:
	cmpl	$31, %ecx
	jmp	LBB3_9
LBB3_6:
	cmpl	$29, %ecx
LBB3_9:
	setl	%al
	movzbl	%al, %eax
LBB3_10:
	popl	%ebp
	retl
	.align	2, 0x90
L3_0_set_8 = LBB3_8-L3$pb
L3_0_set_6 = LBB3_6-L3$pb
L3_0_set_7 = LBB3_7-L3$pb
LJTI3_0:
	.long	L3_0_set_8
	.long	L3_0_set_6
	.long	L3_0_set_8
	.long	L3_0_set_7
	.long	L3_0_set_8
	.long	L3_0_set_7
	.long	L3_0_set_8
	.long	L3_0_set_8
	.long	L3_0_set_7
	.long	L3_0_set_8
	.long	L3_0_set_7
	.long	L3_0_set_8

	.globl	_main
	.align	4, 0x90
_main:                                  ## @main
## BB#0:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%edi
	pushl	%esi
	subl	$28, %esp
	calll	L4$pb
L4$pb:
	popl	%ebx
	movzbl	_monthB-L4$pb(%ebx), %eax
	movzbl	_monthA-L4$pb(%ebx), %ecx
	movl	%ecx, 4(%esp)
	movl	%eax, (%esp)
	calll	_get_month
	movl	%eax, %esi
	movzbl	_dayB-L4$pb(%ebx), %eax
	movzbl	_dayA-L4$pb(%ebx), %ecx
	movl	%ecx, 4(%esp)
	movl	%eax, (%esp)
	calll	_get_day
	movl	%eax, %edi
	cmpl	$-1, %esi
	je	LBB4_2
## BB#1:
	cmpl	$-1, %edi
	je	LBB4_2
## BB#3:
	movl	%edi, 4(%esp)
	movl	%esi, (%esp)
	calll	_check_day
	movl	L_output$non_lazy_ptr-L4$pb(%ebx), %ecx
	movl	%ecx, -16(%ebp)         ## 4-byte Spill
	movl	%eax, (%ecx)
	movl	%edi, 8(%esp)
	movl	%esi, 4(%esp)
	leal	L_.str-L4$pb(%ebx), %eax
	movl	%eax, (%esp)
	calll	_printf
	movl	-16(%ebp), %eax         ## 4-byte Reload
	movl	(%eax), %eax
	movl	%eax, 4(%esp)
	leal	L_.str1-L4$pb(%ebx), %eax
	movl	%eax, (%esp)
	calll	_printf
	xorl	%eax, %eax
	jmp	LBB4_4
LBB4_2:
	movl	%edi, 8(%esp)
	movl	%esi, 4(%esp)
	leal	L_.str-L4$pb(%ebx), %eax
	movl	%eax, (%esp)
	calll	_printf
	movl	L_output$non_lazy_ptr-L4$pb(%ebx), %eax
	movl	(%eax), %eax
	movl	%eax, 4(%esp)
	leal	L_.str1-L4$pb(%ebx), %eax
	movl	%eax, (%esp)
	calll	_printf
	movl	$1, %eax
LBB4_4:
	addl	$28, %esp
	popl	%esi
	popl	%edi
	popl	%ebx
	popl	%ebp
	retl

	.section	__DATA,__data
	.globl	_monthB                 ## @monthB
_monthB:
	.byte	1                       ## 0x1

	.globl	_monthA                 ## @monthA
_monthA:
	.byte	1                       ## 0x1

	.globl	_dayB                   ## @dayB
_dayB:
	.byte	3                       ## 0x3

	.globl	_dayA                   ## @dayA
_dayA:
	.byte	1                       ## 0x1

	.comm	_output,4,2             ## @output
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"Month, Day: (%d, %d)\n"

L_.str1:                                ## @.str1
	.asciz	"Output: %x\n"


	.section	__IMPORT,__pointers,non_lazy_symbol_pointers
L_output$non_lazy_ptr:
	.indirect_symbol	_output
	.long	0

.subsections_via_symbols
