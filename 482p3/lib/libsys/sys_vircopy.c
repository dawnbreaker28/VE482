#include "syslib.h"

int sys_vircopy(src_proc, src_vir, 
	dst_proc, dst_vir, bytes)
endpoint_t src_proc;		/* source process */
vir_bytes src_vir;		/* source virtual address */
endpoint_t dst_proc;		/* destination process */
vir_bytes dst_vir;		/* destination virtual address */
phys_bytes bytes;		/* how many bytes */
{
/* Transfer a block of data.  The source and destination can each either be a
 * process number or SELF (to indicate own process number). Virtual addresses 
 * are offsets within LOCAL_SEG (text, stack, data), or BIOS_SEG. 
 */

  message copy_mess;

  if (bytes == 0L) return(OK);
  copy_mess.CP_SRC_ENDPT = src_proc;
  copy_mess.CP_SRC_ADDR = (long) src_vir;
  copy_mess.CP_DST_ENDPT = dst_proc;
  copy_mess.CP_DST_ADDR = (long) dst_vir;
  copy_mess.CP_NR_BYTES = (long) bytes;

  /* backwards compatability D segs */
  copy_mess.CP_DST_SPACE_OBSOLETE = D_OBSOLETE;
  copy_mess.CP_SRC_SPACE_OBSOLETE = D_OBSOLETE;

  return(_kernel_call(SYS_VIRCOPY, &copy_mess));
}
