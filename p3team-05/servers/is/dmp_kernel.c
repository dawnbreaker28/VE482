/* Debugging dump procedures for the kernel. */

#include "inc.h"
#include <timers.h>
#include <assert.h>
#include <machine/interrupt.h>
#include <minix/endpoint.h>
#include <minix/sysutil.h>
#include <minix/sys_config.h>
#include "kernel/const.h"
#include "kernel/config.h"
#include "kernel/debug.h"
#include "kernel/type.h"
#include "kernel/proc.h"
#include "kernel/ipc.h"

#define LINES 22

#define PRINTRTS(rp) { \
	char *procname = "";	\
	printf(" %s", p_rts_flags_str(rp->p_rts_flags));	\
	if (rp->p_rts_flags & RTS_SENDING)				\
		procname = proc_name(_ENDPOINT_P(rp->p_sendto_e)); \
	else if (rp->p_rts_flags & RTS_RECEIVING)			\
		procname = proc_name(_ENDPOINT_P(rp->p_getfrom_e)); \
	printf(" %-7.7s", procname);	\
}

static int pagelines;

#define PROCLOOP(rp, oldrp) \
	pagelines = 0; \
	for (rp = oldrp; rp < END_PROC_ADDR; rp++) { \
	  oldrp = BEG_PROC_ADDR; \
	  if (isemptyp(rp)) continue; \
	  if (++pagelines > LINES) { oldrp = rp; printf("--more--\n"); break; }\
	  if (proc_nr(rp) == IDLE) 	printf("(%2d) ", proc_nr(rp));  \
	  else if (proc_nr(rp) < 0) 	printf("[%2d] ", proc_nr(rp)); 	\
	  else 				printf(" %2d  ", proc_nr(rp));

#define click_to_round_k(n) \
	((unsigned) ((((unsigned long) (n) << CLICK_SHIFT) + 512) / 1024))

/* Declare some local dump procedures. */
static char *proc_name(int proc_nr);
static char *s_traps_str(int flags);
static char *s_flags_str(int flags);
static char *p_rts_flags_str(int flags);

/* Some global data that is shared among several dumping procedures. 
 * Note that the process table copy has the same name as in the kernel
 * so that most macros and definitions from proc.h also apply here.
 */
struct proc proc[NR_TASKS + NR_PROCS];
struct priv priv[NR_SYS_PROCS];
struct boot_image image[NR_BOOT_PROCS];

extern struct minix_kerninfo *_minix_kerninfo;

/*===========================================================================*
 *				kmessages_dmp				     *
 *===========================================================================*/
void kmessages_dmp()
{
  struct kmessages *kmess;		/* get copy of kernel messages */
  static char print_buf[_KMESS_BUF_SIZE+1]; /* this one is used to print */
  int start;				/* calculate start of messages */
  int r;
  int size;

  assert(_minix_kerninfo);
  kmess = _minix_kerninfo->kmessages;

  /* Try to print the kernel messages. First determine start and copy the
   * buffer into a print-buffer. This is done because the messages in the
   * copy may wrap (the kernel buffer is circular).
   */
  start = ((kmess->km_next + _KMESS_BUF_SIZE) - kmess->km_size) % _KMESS_BUF_SIZE;
  r = 0;
  size = kmess->km_size;
  while (size > 0) {
  	print_buf[r] = kmess->km_buf[(start+r) % _KMESS_BUF_SIZE];
  	r ++;
  	size--;
  }
  print_buf[r] = 0;		/* make sure it terminates */
  printf("Dump of all messages generated by the kernel.\n\n"); 
  printf("%s", print_buf);		/* print the messages */
}

/*===========================================================================*
 *				monparams_dmp				     *
 *===========================================================================*/
void monparams_dmp()
{
  char val[MULTIBOOT_PARAM_BUF_SIZE];
  char *e;
  int r;

  /* Try to get a copy of the boot monitor parameters. */
  if ((r = sys_getmonparams(val, sizeof(val))) != OK) {
      printf("IS: warning: couldn't get copy of monitor params: %d\n", r);
      return;
  }

  /* Append new lines to the result. */
  e = val;
  do {
	e += strlen(e);
	*e++ = '\n';
  } while (*e != 0); 

  /* Finally, print the result. */
  printf("Dump of kernel environment strings set by boot monitor.\n");
  printf("\n%s\n", val);
}

/*===========================================================================*
 *				irqtab_dmp				     *
 *===========================================================================*/
void irqtab_dmp()
{
  int i,r;
  struct irq_hook irq_hooks[NR_IRQ_HOOKS];
  int irq_actids[NR_IRQ_VECTORS];
  struct irq_hook *e;	/* irq tab entry */

  if ((r = sys_getirqhooks(irq_hooks)) != OK) {
      printf("IS: warning: couldn't get copy of irq hooks: %d\n", r);
      return;
  }
  if ((r = sys_getirqactids(irq_actids)) != OK) {
      printf("IS: warning: couldn't get copy of irq mask: %d\n", r);
      return;
  }

#if 0
  printf("irq_actids:");
  for (i= 0; i<NR_IRQ_VECTORS; i++)
	printf(" [%d] = 0x%08x", i, irq_actids[i]);
  printf("\n");
#endif

  printf("IRQ policies dump shows use of kernel's IRQ hooks.\n");
  printf("-h.id- -proc.nr- -irq nr- -policy- -notify id- -masked-\n");
  for (i=0; i<NR_IRQ_HOOKS; i++) {
  	e = &irq_hooks[i];
  	printf("%3d", i);
  	if (e->proc_nr_e==NONE) {
  	    printf("    <unused>\n");
  	    continue;
  	}
  	printf("%10d  ", e->proc_nr_e); 
  	printf("    (%02d) ", e->irq); 
  	printf("  %s", (e->policy & IRQ_REENABLE) ? "reenable" : "    -   ");
  	printf("   %4lu", e->notify_id);
	if (irq_actids[e->irq] & e->id)
		printf("       masked");
	printf("\n");
  }
  printf("\n");
}

/*===========================================================================*
 *				image_dmp				     *
 *===========================================================================*/
void image_dmp()
{
  int m, r;
  struct boot_image *ip;
	
  if ((r = sys_getimage(image)) != OK) {
      printf("IS: warning: couldn't get copy of image table: %d\n", r);
      return;
  }
  printf("Image table dump showing all processes included in system image.\n");
  printf("---name- -nr- flags -stack-\n");
  for (m=0; m<NR_BOOT_PROCS; m++) { 
      ip = &image[m];
      printf("%8s %4d\n", ip->proc_name, ip->proc_nr);
  }
  printf("\n");
}


/*===========================================================================*
 *				kenv_dmp				     *
 *===========================================================================*/
void kenv_dmp()
{
    struct kinfo kinfo;
    struct machine machine;
    int r;
    if ((r = sys_getkinfo(&kinfo)) != OK) {
    	printf("IS: warning: couldn't get copy of kernel info struct: %d\n", r);
    	return;
    }
    if ((r = sys_getmachine(&machine)) != OK) {
    	printf("IS: warning: couldn't get copy of kernel machine struct: %d\n", r);
    	return;
    }

    printf("Dump of kinfo structure.\n\n");
    printf("Kernel info structure:\n");
    printf("- nr_procs:     %3u\n", kinfo.nr_procs); 
    printf("- nr_tasks:     %3u\n", kinfo.nr_tasks); 
    printf("- release:      %.6s\n", kinfo.release); 
    printf("- version:      %.6s\n", kinfo.version); 
    printf("\n");
}

/*===========================================================================*
 *			      s_flags_str				     *
 *===========================================================================*/
static char *s_flags_str(int flags)
{
	static char str[10];
	str[0] = (flags & PREEMPTIBLE)        ? 'P' : '-';
	str[1] = (flags & BILLABLE)           ? 'B' : '-';
	str[2] = (flags & DYN_PRIV_ID)        ? 'D' : '-';
	str[3] = (flags & SYS_PROC)           ? 'S' : '-';
	str[4] = (flags & CHECK_IO_PORT)      ? 'I' : '-';
	str[5] = (flags & CHECK_IRQ)          ? 'Q' : '-';
	str[6] = (flags & CHECK_MEM)          ? 'M' : '-';
	str[7] = '\0';

	return str;
}

/*===========================================================================*
 *			      s_traps_str				     *
 *===========================================================================*/
static char *s_traps_str(int flags)
{
	static char str[10];
	str[0] = (flags & (1 << SEND))  ? 'S' : '-';
	str[1] = (flags & (1 << SENDA)) ? 'A' : '-';
	str[2] = (flags & (1 << RECEIVE))  ? 'R' : '-';
	str[3] = (flags & (1 << SENDREC))  ? 'B' : '-';
	str[4] = (flags & (1 << NOTIFY)) ? 'N' : '-';
	str[5] = '\0';

	return str;
}

/*===========================================================================*
 *				privileges_dmp 				     *
 *===========================================================================*/
void privileges_dmp()
{
  register struct proc *rp;
  static struct proc *oldrp = BEG_PROC_ADDR;
  register struct priv *sp;
  int r, i;

  /* First obtain a fresh copy of the current process and system table. */
  if ((r = sys_getprivtab(priv)) != OK) {
      printf("IS: warning: couldn't get copy of system privileges table: %d\n", r);
      return;
  }
  if ((r = sys_getproctab(proc)) != OK) {
      printf("IS: warning: couldn't get copy of process table: %d\n", r);
      return;
  }

  printf("-nr- -id- -name-- -flags- traps grants -ipc_to--"
    "          -kernel calls-\n");

  PROCLOOP(rp, oldrp)
        r = -1;
        for (sp = &priv[0]; sp < &priv[NR_SYS_PROCS]; sp++) 
            if (sp->s_proc_nr == rp->p_nr) { r ++; break; }
        if (r == -1 && !isemptyp(rp)) {
	    sp = &priv[USER_PRIV_ID];
        }
	printf("(%02u) %-7.7s %s %s %6d",
	       sp->s_id, rp->p_name,
	       s_flags_str(sp->s_flags), s_traps_str(sp->s_trap_mask),
		sp->s_grant_entries);
        for (i=0; i < NR_SYS_PROCS; i += BITCHUNK_BITS) {
	    printf(" %08x", get_sys_bits(sp->s_ipc_to, i));
       	}

	printf(" ");
        for (i=0; i < NR_SYS_CALLS; i += BITCHUNK_BITS) {
	    printf(" %08x", sp->s_k_call_mask[i/BITCHUNK_BITS]);
       	}
	printf("\n");

  }
}

/*===========================================================================*
 *			       p_rts_flags_str 				     *
 *===========================================================================*/
static char *p_rts_flags_str(int flags)
{
	static char str[10];
	str[0] = (flags & RTS_PROC_STOP) ? 's' : '-';
	str[1] = (flags & RTS_SENDING)  ? 'S' : '-';
	str[2] = (flags & RTS_RECEIVING)    ? 'R' : '-';
	str[3] = (flags & RTS_SIGNALED)    ? 'I' : '-';
	str[4] = (flags & RTS_SIG_PENDING)    ? 'P' : '-';
	str[5] = (flags & RTS_P_STOP)    ? 'T' : '-';
	str[6] = (flags & RTS_NO_PRIV) ? 'p' : '-';
	str[7] = '\0';

	return str;
}

/*===========================================================================*
 *				proctab_dmp    				     *
 *===========================================================================*/
#if defined(__i386__)
void proctab_dmp(void)
{
/* Proc table dump */

  register struct proc *rp;
  static struct proc *oldrp = BEG_PROC_ADDR;
  int r;

  /* First obtain a fresh copy of the current process table. */
  if ((r = sys_getproctab(proc)) != OK) {
      printf("IS: warning: couldn't get copy of process table: %d\n", r);
      return;
  }

  printf("\n-nr-----gen---endpoint-name--- -prior-quant- -user----sys-rtsflags-from/to-\n");

  PROCLOOP(rp, oldrp)
	printf(" %5d %10d ", _ENDPOINT_G(rp->p_endpoint), rp->p_endpoint);
	printf("%-8.8s %5u %5u %6u %6u ",
	       rp->p_name,
	       rp->p_priority,
	       rp->p_quantum_size_ms,
	       rp->p_user_time, rp->p_sys_time);
	PRINTRTS(rp);
	printf("\n");
  }
}
#endif				/* defined(__i386__) */

#if defined(__arm__)
void proctab_dmp(void)
{
    /* LSC FIXME: Not implemented for arm */
}
#endif				/* defined(__arm__) */

/*===========================================================================*
 *				procstack_dmp  				     *
 *===========================================================================*/
void procstack_dmp()
{
/* Proc table dump, with stack */

  register struct proc *rp;
  static struct proc *oldrp = BEG_PROC_ADDR;
  int r;

  /* First obtain a fresh copy of the current process table. */
  if ((r = sys_getproctab(proc)) != OK) {
      printf("IS: warning: couldn't get copy of process table: %d\n", r);
      return;
  }

  printf("\n-nr-rts flags--      --stack--\n");

  PROCLOOP(rp, oldrp)
	PRINTRTS(rp);
	sys_sysctl_stacktrace(rp->p_endpoint);
  }
}

/*===========================================================================*
 *				proc_name    				     *
 *===========================================================================*/
static char *proc_name(proc_nr)
int proc_nr;
{
  struct proc *p;
  if (proc_nr == ANY) return "ANY";
  if (proc_nr == NONE) return "NONE";	/* bogus */
  if (proc_nr < -NR_TASKS || proc_nr >= NR_PROCS) return "BOGUS";
  p = proc_addr(proc_nr);
  if (isemptyp(p)) return "EMPTY";	/* bogus */
  return p->p_name;
}

