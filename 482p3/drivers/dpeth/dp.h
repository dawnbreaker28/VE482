/*
**  File:	eth.h	Version 1.00,	Jan. 14, 1997
**
**  Author:	Giovanni Falzoni <gfalzoni@inwind.it>
**
**  Interface description for ethernet device driver
**
**  $Log$
**  Revision 1.5  2006/07/10 12:43:38  philip
**  Safecopy support in ethernet drivers.
**
**  Revision 1.4  2005/09/04 18:52:16  beng
**  Giovanni's fixes to dpeth:
**  Date: Sat, 03 Sep 2005 11:05:22 +0200
**  Subject: Minix 3.0.8
**
**  Revision 1.3  2005/08/03 11:53:34  jnherder
**  Miscellaneous cleanups.
**
**  Revision 1.2  2005/08/02 15:30:35  jnherder
**  Various updates to support dynamically starting drivers.
**  Output during initialization should be suppressed. Unless an error occurs.
**  Note that main() can now be main(int argc, char **argv) and arguments can
**  be passed when bringing up the driver.
**
**  Revision 1.1  2005/06/29 10:16:46  beng
**  Import of dpeth 3c501/3c509b/.. ethernet driver by
**  Giovanni Falzoni <fgalzoni@inwind.it>.
**
**  Revision 2.0  2005/06/26 16:16:46  lsodgf0
**  Initial revision for Minix 3.0.6
*/

#include <sys/null.h>

#undef  ENABLE_3C501
#undef  ENABLE_3C503
#undef  ENABLE_3C509
#undef  ENABLE_NE2000
#undef  ENABLE_WDETH
#undef  ENABLE_DP8390

#define ENABLE_3C501	1	/* enable 3Com Etherlink I board	 */
#define ENABLE_3C503	1	/* enable 3Com Etherlink II board 	 */
#define ENABLE_3C509	1	/* enable 3Com Etherlink III board 	 */
#define ENABLE_NE2000	1	/* enable Novell N2000 board      	 */
#define ENABLE_WDETH	1	/* enable Western Digital WD80x3  	 */

#define ENABLE_DP8390	(ENABLE_3C503|ENABLE_WDETH|ENABLE_NE2000)
#define	HAVE_BUFFERS	(ENABLE_3C501|ENABLE_3C509)

#define NOT(x) (~(x))

#if debug == 1
#	define DEBUG(statm) statm
#else
#	define DEBUG(statm)
#endif

typedef struct _m_hdr_t {	/* Buffer handling header */
  struct _m_hdr_t *next;
  int size;
} m_hdr_t;

typedef struct _buff_t {	/* Receive/Transmit buffer header */
  struct _buff_t *next;
  int size;
  int client;
  char buffer[2];
} buff_t;

struct dpeth;
struct iovec_dat;
typedef void (*dp_eth_t) (struct dpeth *);
typedef void (*dp_send_recv_t) (struct dpeth *, int, int);

#if ENABLE_DP8390 == 1
typedef void (*dp_user2nicf_t) (struct dpeth *, int, int);
typedef void (*dp_nic2userf_t) (struct dpeth *, int, int);
typedef void (*dp_getblock_t) (struct dpeth *, u16_t, int, void *);
#endif

#define SENDQ_NR	2	/* Size of the send queue	 */
#define IOVEC_NR	16	/* Number of IOVEC entries at a time */

typedef struct iovec_dat_s {
  iovec_s_t iod_iovec[IOVEC_NR];
  int iod_iovec_s;
  endpoint_t iod_proc_nr;
  cp_grant_id_t iod_grant;
  vir_bytes iod_iovec_offset;
} iovec_dat_s_t;

typedef struct dpeth {
  /* The de_base_port field is the starting point of the probe. The
   * conf routine also fills de_linmem and de_irq. If the probe routine
   * knows the irq and/or memory address because they are hardwired in
   * the board, the probe should modify these fields. Futhermore, the
   * probe routine should also fill in de_initf and de_stopf fields
   * with the appropriate function pointers and set de_prog_IO iff
   * programmed I/O is to be used.
   * 
   * The initf function fills the following fields. Only cards that do
   * programmed I/O fill in the de_data_port field. In addition, the
   * init routine has to fill in the sendq data structures. */

  /* Board hardware interface */
  port_t de_base_port;
  port_t de_data_port;		/* For boards using Prog. I/O for xmit/recv */

  int de_irq;
  int de_int_pending;
  int de_hook;			/* interrupt hook at kernel */

  char de_name[8];

#define DEI_DEFAULT	0x8000

  phys_bytes de_linmem;		/* For boards using shared memory */
  vir_bytes de_memoffs;
  int de_ramsize;		/* Size of on board memory	 */
  int de_offset_page;		/* Offset of shared memory page	 */

  /* Board specific functions */
  dp_eth_t de_initf;
  dp_eth_t de_stopf;
  dp_eth_t de_resetf;
  dp_eth_t de_flagsf;
  dp_eth_t de_getstatsf;
  dp_eth_t de_dumpstatsf;
  dp_eth_t de_interruptf;
  dp_send_recv_t de_recvf;
  dp_send_recv_t de_sendf;

  ether_addr_t de_address;	/* Ethernet Address */
  eth_stat_t de_stat;		/* Ethernet Statistics */
  unsigned long bytes_Tx;	/* Total bytes sent/received */
  unsigned long bytes_Rx;

#define	SA_ADDR_LEN	sizeof(ether_addr_t)

  int de_flags;			/* Send/Receive mode (Configuration) */

#define DEF_EMPTY	0x0000
#define DEF_READING	0x0001
#define DEF_RECV_BUSY	0x0002
#define DEF_ACK_RECV	0x0004
#define DEF_SENDING	0x0010
#define DEF_XMIT_BUSY	0x0020
#define DEF_ACK_SEND	0x0040
#define DEF_PROMISC	0x0100
#define DEF_MULTI	0x0200
#define DEF_BROAD	0x0400
#define DEF_ENABLED	0x2000
#define DEF_STOPPED	0x4000

  int de_mode;			/* Status of the Interface */

#define DEM_DISABLED	0x0000
#define DEM_SINK	0x0001
#define DEM_ENABLED	0x0002

  /* Temporary storage for RECV/SEND requests */
  iovec_dat_s_t de_read_iovec;
  iovec_dat_s_t de_write_iovec;
  vir_bytes de_read_s;
  vir_bytes de_send_s;
  int de_client;
/*
  message de_sendmsg;
  iovec_dat_t de_tmp_iovec;
*/
#if ENABLE_DP8390 == 1
  /* For use by NS DP8390 driver */
  port_t de_dp8390_port;
  int de_prog_IO;
  int de_16bit;
  int de_startpage;
  int de_stoppage;

  /* Do it yourself send queue */
  struct sendq {
	int sq_filled;		/* This buffer contains a packet */
	int sq_size;		/* with this size */
	int sq_sendpage;	/* starting page of the buffer */
  } de_sendq[SENDQ_NR];
  int de_sendq_nr;
  int de_sendq_head;		/* Enqueue at the head */
  int de_sendq_tail;		/* Dequeue at the tail */

  dp_user2nicf_t de_user2nicf;
  dp_nic2userf_t de_nic2userf;
  dp_getblock_t de_getblockf;
#endif

#if ENABLE_3C509 == 1
  /* For use by 3Com Etherlink III (3c509) driver */
  port_t de_id_port;
  port_t de_if_port;
#endif

#if ENABLE_3C501 == 1 ||  ENABLE_3C509 == 1
  /* For use by 3Com Etherlink (3c501 and 3c509) driver */
  buff_t *de_recvq_head;
  buff_t *de_recvq_tail;
  buff_t *de_xmitq_head;
  buff_t *de_xmitq_tail;
  u16_t de_recv_mode;
  clock_t de_xmit_start;
#endif

} dpeth_t;

/*
 *	Function definitions
 */

/* dp.c */
void dp_next_iovec(iovec_dat_s_t * iovp);

/* devio.c */
#if defined USE_IOPL
#include <machine/portio.h>
#else
unsigned int inb(unsigned short int);
unsigned int inw(unsigned short int);
void insb(unsigned short int, endpoint_t, void *, int);
void insw(unsigned short int, int, void *, int);
void outb(unsigned short int, unsigned long);
void outw(unsigned short int, unsigned long);
void outsb(unsigned short int, endpoint_t, void *, int);
void outsw(unsigned short int, int, void *, int);
#endif

/* netbuff.c */
void *alloc_buff(dpeth_t *, int);
void free_buff(dpeth_t *, void *);
void init_buff(dpeth_t *, buff_t **);
void mem2user(dpeth_t *, buff_t *);
void user2mem(dpeth_t *, buff_t *);

/* 3c501.c */
#if ENABLE_3C501 == 1
int el1_probe(dpeth_t *);
#else
#define el1_probe(x) (0)
#endif

/* 3c503.c */
#if ENABLE_3C503 == 1
int el2_probe(dpeth_t *);
#else
#define el2_probe(x) (0)
#endif

/* 3c509.c */
#if ENABLE_3C509 == 1
int el3_probe(dpeth_t *);
#else
#define el3_probe(x) (0)
#endif

/* ne.c */
#if ENABLE_NE2000 == 1
int ne_probe(dpeth_t * dep);
#else
#define ne_probe(x) (0)
#endif

/* wd.c */
#if ENABLE_WDETH == 1
int wdeth_probe(dpeth_t * dep);
#else
#define wdeth_probe(x) (0)
#endif

#define lock()	 (++dep->de_int_pending,sys_irqdisable(&dep->de_hook))
#define unlock() do{int i=(--dep->de_int_pending)?0:sys_irqenable(&dep->de_hook);(void) i;}while(0)
#define milli_delay(t) tickdelay(1)

/** dp.h **/
