	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 10
	.globl	_error_out
	.align	4, 0x90
_error_out:                             ## @error_out
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp0:
	.cfi_def_cfa_offset 16
Ltmp1:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp2:
	.cfi_def_cfa_register %rbp
	movq	_output@GOTPCREL(%rip), %rax
	movl	$14, (%rax)
	popq	%rbp
	retq
	.cfi_endproc

	.globl	_get_month
	.align	4, 0x90
_get_month:                             ## @get_month
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp3:
	.cfi_def_cfa_offset 16
Ltmp4:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp5:
	.cfi_def_cfa_register %rbp
	cmpl	$9, %edi
	ja	LBB1_2
## BB#1:
	movzbl	%sil, %ecx
	cmpl	$10, %ecx
	jae	LBB1_2
## BB#3:
	movzbl	%dil, %eax
	imull	 $10, %eax
	addl	%ecx, %eax
	popq	%rbp
	retq
LBB1_2:
	callq	_error_out
	movl	$-1, %eax
	popq	%rbp
	retq
	.cfi_endproc

	.globl	_get_day
	.align	4, 0x90
_get_day:                               ## @get_day
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp6:
	.cfi_def_cfa_offset 16
Ltmp7:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp8:
	.cfi_def_cfa_register %rbp
	cmpl	$9, %edi
	ja	LBB2_2
## BB#1:
	movzbl	%sil, %ecx
	cmpl	$10, %ecx
	jae	LBB2_2
## BB#3:
	movzbl	%dil, %eax
	imull	 $10, %eax
	addl	%ecx, %eax
	popq	%rbp
	retq
LBB2_2:
	callq	_error_out
	movl	$-1, %eax
	popq	%rbp
	retq
	.cfi_endproc

	.globl	_check_day
	.align	4, 0x90
_check_day:                             ## @check_day
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp9:
	.cfi_def_cfa_offset 16
Ltmp10:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp11:
	.cfi_def_cfa_register %rbp
                                        ## kill: EDI<def> EDI<kill> RDI<def>
	xorl	%eax, %eax
	testl	%edi, %edi
	je	LBB3_10
## BB#1:
	testl	%esi, %esi
	je	LBB3_10
## BB#2:
	cmpl	$12, %edi
	jg	LBB3_10
## BB#3:
	cmpl	$31, %esi
	jg	LBB3_10
## BB#4:
	decl	%edi
	cmpl	$11, %edi
	ja	LBB3_10
## BB#5:
	leaq	LJTI3_0(%rip), %rax
	movslq	(%rax,%rdi,4), %rcx
	addq	%rax, %rcx
	jmpq	*%rcx
LBB3_8:
	cmpl	$32, %esi
	jmp	LBB3_9
LBB3_7:
	cmpl	$31, %esi
	jmp	LBB3_9
LBB3_6:
	cmpl	$29, %esi
LBB3_9:
	setl	%al
	movzbl	%al, %eax
LBB3_10:
	popq	%rbp
	retq
	.cfi_endproc
	.align	2, 0x90
L3_0_set_8 = LBB3_8-LJTI3_0
L3_0_set_6 = LBB3_6-LJTI3_0
L3_0_set_7 = LBB3_7-LJTI3_0
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
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp12:
	.cfi_def_cfa_offset 16
Ltmp13:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp14:
	.cfi_def_cfa_register %rbp
	pushq	%r15
	pushq	%r14
	pushq	%r12
	pushq	%rbx
Ltmp15:
	.cfi_offset %rbx, -48
Ltmp16:
	.cfi_offset %r12, -40
Ltmp17:
	.cfi_offset %r14, -32
Ltmp18:
	.cfi_offset %r15, -24
	movzbl	_monthA(%rip), %esi
	movzbl	_monthB(%rip), %edi
	callq	_get_month
	movl	%eax, %r14d
	movzbl	_dayA(%rip), %esi
	movzbl	_dayB(%rip), %edi
	callq	_get_day
	movl	%eax, %ebx
	cmpl	$-1, %r14d
	je	LBB4_2
## BB#1:
	cmpl	$-1, %ebx
	je	LBB4_2
## BB#3:
	movl	%r14d, %edi
	movl	%ebx, %esi
	callq	_check_day
	movq	_output@GOTPCREL(%rip), %r12
	movl	%eax, (%r12)
	leaq	L_.str(%rip), %rdi
	xorl	%r15d, %r15d
	xorl	%eax, %eax
	movl	%r14d, %esi
	movl	%ebx, %edx
	callq	_printf
	movl	(%r12), %esi
	leaq	L_.str1(%rip), %rdi
	xorl	%eax, %eax
	callq	_printf
	jmp	LBB4_4
LBB4_2:
	leaq	L_.str(%rip), %rdi
	xorl	%eax, %eax
	movl	%r14d, %esi
	movl	%ebx, %edx
	callq	_printf
	movq	_output@GOTPCREL(%rip), %rax
	movl	(%rax), %esi
	leaq	L_.str1(%rip), %rdi
	xorl	%eax, %eax
	callq	_printf
	movl	$1, %r15d
LBB4_4:
	movl	%r15d, %eax
	popq	%rbx
	popq	%r12
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
	.cfi_endproc

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


.subsections_via_symbols
