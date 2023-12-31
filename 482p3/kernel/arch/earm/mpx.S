/* This file is part of the lowest layer of the MINIX kernel.  (The other part 
 * is "proc.c".)  The lowest layer does process switching and message handling. 
 *
 * Kernel is entered either because of kernel-calls, ipc-calls, interrupts or
 * exceptions. TSS is set so that the kernel stack is loaded. The user context is
 * saved to the proc table and the handler of the event is called. Once the
 * handler is done, switch_to_user() function is called to pick a new process,
 * finish what needs to be done for the next process to run, sets its context
 * and switch to userspace.
 */

#include "kernel/kernel.h" /* configures the kernel */

/* sections */

#include <machine/vm.h>
#include "kernel/kernel.h"
#include <minix/config.h>
#include <minix/const.h>
#include <minix/com.h>
#include <machine/asm.h>
#include <machine/interrupt.h>
#include "archconst.h"
#include "kernel/const.h"
#include "kernel/proc.h"
#include "sconst.h"
#include <machine/multiboot.h>
#include <machine/ipcconst.h>
#include <machine/cpu.h>
#include "omap_intr.h"

#include "arch_proto.h" /* K_STACK_SIZE */

IMPORT(svc_stack)

/*
 * Adjust lr, switch to SVC mode, and push pc/psr when exception triggered
 * The 'lr_offset' argument holds the adjustment. It differs based on
 * which mode the CPU is in.
 */
.macro switch_to_svc lr_offset
	sub	lr, lr, #\lr_offset
	srsdb	sp!, #MODE_SVC
	cps	#MODE_SVC
.endm

/*
 * Test if the exception/interrupt occured in the kernel.
 * Jump to 'label' argument if it occurred in the kernel.
 *
 * NOTE: switch_to_svc must be called first
 */
.macro test_int_in_kernel, label
	push	{r3}
	ldr	r3, [sp, #8] /* spsr */
	and	r3, r3, #PSR_MODE_MASK
	cmp	r3, #MODE_USR
	pop	{r3}
	bne	\label  /* In-kernel handling */
.endm

/* Save the register context to the proc structure */
.macro save_process_ctx
	add	sp, sp, #8	/* srsdb pushed cpsr and pc on the stack */
	ldr	lr, [sp]	/* lr = proc_ptr */
	stm	lr, {r0-r14}^	/* proc_ptr->p_reg.r0-r14 = r0-r14 */
	ldr	r12, [sp, #-8]	/* r12 = pc stored on the stack */
	str	r12, [lr, #PCREG] /* proc_ptr->p_reg.pc = r12 */
	ldr	r12, [sp, #-4]	/* r12 = cpsr stored on the stack */
	str	r12, [lr, #PSREG] /* proc_ptr->p_reg.psr = r12 */
.endm

.macro exception_handler exc_name, exc_num, lr_offset
ENTRY(\exc_name\()_entry)
	switch_to_svc \lr_offset
	test_int_in_kernel \exc_name\()_entry_nested

\exc_name\()entry_from_user:
	save_process_ctx

	/* save the pointer to the current process */
	ldr	fp, [sp]
	/* save the exception pc (saved lr_user) */
	ldr	r4, [fp, #PCREG]

	/* stop user process cycles */
	mov	r0, fp  /* first param: caller proc ptr */
	mov	fp, #0  /* for stack trace */
	bl	_C_LABEL(context_stop)

	/*
	 * push a pointer to the interrupt state pushed by the cpu and the
	 * vector number pushed by the vector handler just before calling
	 * exception_entry and call the exception handler.
	 */
	mov	r0, #0	/* it's not a nested exception */
	mov	r1, r4          /* saved lr */
	mov 	r2, #\exc_num	/* vector number */
	bl 	_C_LABEL(exception_handler)

	b	_C_LABEL(switch_to_user)

\exc_name\()_entry_nested:
	push	{r0-r12, lr}
	mov	r0, #1  /* it's a nested exception */
	add	r1, sp, #56     /* saved lr */
	mov	r2, #\exc_num	/* vector number */
	bl	_C_LABEL(exception_handler)
	pop	{r0-r12, lr}
	rfeia	sp!
.endm


/* Exception handlers */
exception_handler data_abort DATA_ABORT_VECTOR 8
exception_handler prefetch_abort PREFETCH_ABORT_VECTOR 4
exception_handler undefined_inst UNDEFINED_INST_VECTOR 4


ENTRY(irq_entry)
	switch_to_svc 4
	test_int_in_kernel irq_entry_from_kernel

irq_entry_from_user:
	save_process_ctx

	/* save the pointer to the current process */
	ldr	fp, [sp]

	push	{fp}    /* save caller proc ptr */

	/* stop user process cycles */
	mov	r0, fp  /* first param: caller proc ptr */
	mov	fp, #0  /* for stack trace */
	bl	_C_LABEL(context_stop)

	/* get irq num */
	ldr	r3, =OMAP3_INTR_SIR_IRQ
	ldr	r0, [r3]
	and	r0, r0, #OMAP3_INTR_ACTIVEIRQ_MASK /* irq */
	/* call handler */
	bl	_C_LABEL(irq_handle)	/* irq_handle(irq) */

	pop	{fp}    /* caller proc ptr */

	/* allow new interrupts */
	mov	r1, #OMAP3_INTR_NEWIRQAGR
	ldr	r3, =OMAP3_INTR_CONTROL
	str	r1, [r3]

	/* data synchronization barrier */
	dsb

	b	_C_LABEL(switch_to_user)

irq_entry_from_kernel:
	push	{r0-r12, lr}
	bl	_C_LABEL(context_stop_idle)

	/* get irq num */
	ldr	r3, =OMAP3_INTR_SIR_IRQ
	ldr	r0, [r3]
	and	r0, r0, #OMAP3_INTR_ACTIVEIRQ_MASK /* irq */
	/* call handler */
	bl	_C_LABEL(irq_handle)	/* irq_handle(irq) */

	/* allow new interrupts */
	mov	r1, #OMAP3_INTR_NEWIRQAGR
	ldr	r3, =OMAP3_INTR_CONTROL
	str	r1, [r3]

	/* data synchronization barrier */
	dsb

	pop	{r0-r12, lr}
	rfeia	sp!


/*
 * supervisor call (SVC) kernel entry point
 */
ENTRY(svc_entry)
	srsdb	sp!, #MODE_SVC
	save_process_ctx

	/* save the pointer to the current process */
	ldr	fp, [sp]

	cmp	r3, #KERVEC
	beq	kernel_call_entry
	cmp	r3, #IPCVEC
	beq	ipc_entry
	b	invalid_svc

/*
 * kernel call is only from a process to kernel
 */
ENTRY(kernel_call_entry)
	/*
	 * pass the syscall arguments from userspace to the handler.
	 * save_process_ctx() does not clobber these registers, they are still
	 * set as the userspace has set them
	 */
	push	{fp}    /* save caller proc ptr */
	push	{r0}    /* save msg ptr so it's not clobbered */

	/* stop user process cycles */
	mov	r0, fp  /* first param: caller proc ptr */
	mov	fp, #0  /* for stack trace */
	bl	_C_LABEL(context_stop)

	pop	{r0} /* first param: msg ptr */
	pop	{r1} /* second param: caller proc ptr */
	bl	_C_LABEL(kernel_call)

	b	_C_LABEL(switch_to_user)

/*
 * IPC is only from a process to kernel
 */
ENTRY(ipc_entry)
	/*
	 * pass the syscall arguments from userspace to the handler.
	 * save_process_ctx() does not clobber these registers, they are still
	 * set as the userspace have set them
	 */
	push	{fp}    /* save caller proc ptr */
	push	{r0-r2} /* save regs so they're not clobbered */

	/* stop user process cycles */
	mov	r0, fp  /* first param: caller proc ptr */
	mov	fp, #0  /* for stack trace */
	bl	_C_LABEL(context_stop)

	pop	{r0-r2} /* restore regs */
	bl	_C_LABEL(do_ipc)

	/* restore the current process pointer and save the return value */
	pop	{fp}    /* caller proc ptr */
	str	r0, [fp, #REG0]

	b	_C_LABEL(switch_to_user)

ENTRY(invalid_svc)
	b .

ENTRY(restore_user_context)
	/* sp holds the proc ptr */
	mov sp, r0

	/* Set SPSR and LR for return */
	ldr r0, [sp, #PSREG]
	msr spsr_fsxc, r0
	ldr lr, [sp, #PCREG]

	/* Restore user-mode registers from proc struct */
	ldm sp, {r0-r14}^

	ldr sp, =_C_LABEL(svc_stack)
	ldr sp, [sp]

	/* To user mode! */
	movs pc, lr

/*===========================================================================*/
/*				data					     */
/*===========================================================================*/

.data
.short	0x526F	/* this must be the first data entry (magic #) */
.bss
.data
.balign 4
k_initial_stack:
.space	K_STACK_SIZE
LABEL(__k_unpaged_k_initial_stktop)

/*
 * the kernel stack
 */
k_boot_stack:
.space	K_STACK_SIZE	/* kernel stack */ /* FIXME use macro here */
LABEL(k_boot_stktop)	/* top of kernel stack */

.balign K_STACK_SIZE
LABEL(k_stacks_start)

/* two pages for each stack, one for data, other as a sandbox */
.space	2 * (K_STACK_SIZE * CONFIG_MAX_CPUS)

LABEL(k_stacks_end)

/* top of kernel stack */
