
#ifndef _REGION_H
#define _REGION_H 1

#include <minix/callnr.h>
#include <minix/com.h>
#include <minix/config.h>
#include <minix/const.h>
#include <minix/ds.h>
#include <minix/endpoint.h>
#include <minix/keymap.h>
#include <minix/minlib.h>
#include <minix/type.h>
#include <minix/ipc.h>
#include <minix/sysutil.h>
#include <minix/syslib.h>
#include <minix/const.h>

#include "phys_region.h"
#include "memtype.h"
#include "vm.h"

struct phys_block {
#if SANITYCHECKS
	u32_t			seencount;
#endif
	phys_bytes		phys;	/* physical memory */
	u8_t			refcount;	/* Refcount of these pages */

	/* what kind of memory is it? */
	mem_type_t		*memtype;

	/* first in list of phys_regions that reference this block */
	struct phys_region	*firstregion;	
};

typedef struct vir_region {
	vir_bytes	vaddr;	/* virtual address, offset from pagetable */
	vir_bytes	length;	/* length in bytes */
	struct phys_region	**physblocks;
	u16_t		flags;
	struct vmproc *parent;	/* Process that owns this vir_region. */
	mem_type_t	*memtype; /* Default instantiated memory type. */
	int		remaps;
	u32_t		id;     /* unique id */

	union {
		phys_bytes phys;
		struct {
			endpoint_t ep;
			vir_bytes vaddr;
			int id;
		} shared;
	} param;

	/* AVL fields */
	struct vir_region *lower, *higher;
	int		factor;
} region_t;

/* Mapping flags: */
#define VR_WRITABLE	0x001	/* Process may write here. */
#define VR_PHYS64K	0x004	/* Physical memory must be 64k aligned. */
#define VR_LOWER16MB	0x008
#define VR_LOWER1MB	0x010
#define VR_CONTIG	0x020	/* Must be physically contiguous. */
#define VR_SHARED	0x040
#define VR_UNINITIALIZED 0x080	/* Do not clear after allocation  */

/* Mapping type: */
#define VR_ANON		0x100	/* Memory to be cleared and allocated */
#define VR_DIRECT	0x200	/* Mapped, but not managed by VM */

/* map_page_region flags */
#define MF_PREALLOC	0x01

#endif

