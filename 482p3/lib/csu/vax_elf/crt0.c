/* $NetBSD: crt0.c,v 1.12 2011/03/07 05:09:11 joerg Exp $ */

/*
 * Copyright (c) 1999 Matt Thomas
 * Copyright (c) 1995 Christopher G. Demetriou
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *          This product includes software developed for the
 *          NetBSD Project.  See http://www.NetBSD.org/ for
 *          information about NetBSD.
 * 4. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * <<Id: LICENSE,v 1.2 2000/06/14 15:57:33 cgd Exp>>
 */

#include "common.h"

void ___start(int, char **, char **, void (*cleanup)(void),
    const Obj_Entry *, struct ps_strings *);

__asm(" .text;"
"	.align	2;"
"	.globl	_start;"
"	.globl	__start;"
"__start:;"
"_start:;"
"	.word	0x0101;"
"	pushl	%r9;"		/* ps_strings */
"	pushl	%r8;"		/* obj */
"	pushl	%r7;"		/* cleanup */
"	movl	(%r6),%r0;"	/* argc */
"	pushal	8(%r6)[%r0];"	/* envp = &argv[argc + 1] */
"	pushal	4(%r6);"	/* argv */
"	pushl	%r0;"		/* argc */
"	calls	$6,___start;"
	);

void
___start(int argc, char **argv, char **envp,
    void (*cleanup)(void),			/* from shared loader */
    const Obj_Entry *obj,			/* from shared loader */
    struct ps_strings *ps_strings)
{
	environ = envp;

	if ((__progname = argv[0]) != NULL) {	/* NULL ptr if argc = 0 */
		if ((__progname = _strrchr(__progname, '/')) == NULL)
			__progname = argv[0];
		else
			__progname++;
	}

	if (ps_strings != (struct ps_strings *)0)
		__ps_strings = ps_strings;

#ifdef DYNAMIC
	if (&rtld_DYNAMIC != NULL)
		_rtld_setup(cleanup, obj);
#endif

	_libc_init();

#ifdef MCRT0
	atexit(_mcleanup);
	monstartup((u_long)&_eprol, (u_long)&_etext);
#endif

	atexit(_fini);
	_init();

	exit(main(argc, argv, environ));
}

/*
 * NOTE: Leave the RCS ID _after_ __start(), in case it gets placed in .text.
 */
#if defined(LIBC_SCCS) && !defined(lint)
__RCSID("$NetBSD: crt0.c,v 1.12 2011/03/07 05:09:11 joerg Exp $");
#endif /* LIBC_SCCS and not lint */

#include "common.c"
