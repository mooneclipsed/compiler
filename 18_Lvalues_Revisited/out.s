	.text
	.data
	.globl	a
a:	.byte	0
	.data
	.globl	b
b:	.quad	0
	.data
	.globl	d
d:	.long	0
	.data
	.globl	e
e:	.quad	0
	.text
	.globl	main
	.type	main, @function
main:
	pushq	%rbp
	movq	%rsp, %rbp
	leaq	a(%rip), %r8
	movq	%r8, b(%rip)
	movq	$19, %r8
	movq	b(%rip), %r9
	movb	%r8b, (%r9)
	movzbq	a(%rip), %r8
	movq	%r8, %rdi
	call	printint
	movq	%rax, %r9
	leaq	d(%rip), %r8
	movq	%r8, e(%rip)
	movq	$12, %r8
	movq	e(%rip), %r9
	movq	%r8, (%r9)
	movzbl	d(%rip), %r8
	movq	%r8, %rdi
	call	printint
	movq	%rax, %r9
	movq	$0, %r8
	movl	%r8d, %eax
	jmp	L1
L1:
	popq	%rbp
	ret
