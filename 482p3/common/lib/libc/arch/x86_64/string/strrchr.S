/*
 * Written by J.T. Conklin <jtc@acorntoolworks.com>
 * Public domain.
 */

#include <machine/asm.h>

#if defined(LIBC_SCCS)
	RCSID("$NetBSD: strrchr.S,v 1.2 2009/07/17 19:37:57 dsl Exp $")
#endif

ENTRY(strrchr)
	movzbq	%sil,%rcx

	/* zero return value */
	xorq	%rax,%rax

	/*
	 * Align to word boundary.
	 * Consider unrolling loop?
	 */
.Lalign:
	testb	$7,%dil
	je	.Lword_aligned
	movb	(%rdi),%dl
	cmpb	%cl,%dl
	cmoveq	%rdi,%rax
	incq	%rdi
	testb	%dl,%dl
	jne	.Lalign
	jmp	.Ldone

.Lword_aligned:
	/* copy char to all bytes in word */
	movb	%cl,%ch
	movq	%rcx,%rdx
	salq	$16,%rcx
	orq	%rdx,%rcx
	movq	%rcx,%rdx
	salq	$32,%rcx
	orq	%rdx,%rcx

	movabsq	$0x0101010101010101,%r8
	movabsq	$0x8080808080808080,%r9

	/* Check whether any byte in the word is equal to ch or 0. */
	_ALIGN_TEXT
.Lloop:
	movq	(%rdi),%rdx
	addq	$8,%rdi
	movq	%rdx,%rsi
	subq	%r8,%rdx
	xorq	%rcx,%rsi
	subq	%r8,%rsi
	orq	%rsi,%rdx
	testq	%r9,%rdx
	je	.Lloop

	/*
	 * In rare cases, the above loop may exit prematurely. We must
	 * return to the loop if none of the bytes in the word match
	 * ch or are equal to 0.
	 */

	movb	-8(%rdi),%dl
	cmpb	%cl,%dl		/* 1st byte == ch? */
	jne	1f
	leaq	-8(%rdi),%rax
1:	testb	%dl,%dl		/* 1st byte == 0? */
	je	.Ldone

	movb	-7(%rdi),%dl
	cmpb	%cl,%dl		/* 2nd byte == ch? */
	jne	1f
	leaq	-7(%rdi),%rax
1:	testb	%dl,%dl		/* 2nd byte == 0? */
	je	.Ldone

	movb	-6(%rdi),%dl
	cmpb	%cl,%dl		/* 3rd byte == ch? */
	jne	1f
	leaq	-6(%rdi),%rax
1:	testb	%dl,%dl		/* 3rd byte == 0? */
	je	.Ldone

	movb	-5(%rdi),%dl
	cmpb	%cl,%dl		/* 4th byte == ch? */
	jne	1f
	leaq	-5(%rdi),%rax
1:	testb	%dl,%dl		/* 4th byte == 0? */
	je	.Ldone

	movb	-4(%rdi),%dl
	cmpb	%cl,%dl		/* 5th byte == ch? */
	jne	1f
	leaq	-4(%rdi),%rax
1:	testb	%dl,%dl		/* 5th byte == 0? */
	je	.Ldone

	movb	-3(%rdi),%dl
	cmpb	%cl,%dl		/* 6th byte == ch? */
	jne	1f
	leaq	-3(%rdi),%rax
1:	testb	%dl,%dl		/* 6th byte == 0? */
	je	.Ldone

	movb	-2(%rdi),%dl
	cmpb	%cl,%dl		/* 7th byte == ch? */
	jne	1f
	leaq	-2(%rdi),%rax
1:	testb	%dl,%dl		/* 7th byte == 0? */
	je	.Ldone

	movb	-1(%rdi),%dl
	cmpb	%cl,%dl		/* 8th byte == ch? */
	jne	1f
	leaq	-1(%rdi),%rax
1:	testb	%dl,%dl		/* 8th byte == 0? */
	jne	.Lloop

.Ldone:
	ret

STRONG_ALIAS(rindex,strrchr)
