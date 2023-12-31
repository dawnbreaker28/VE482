#define _POSIX_SOURCE      1	/* tell headers to include POSIX stuff */
#define _MINIX             1	/* tell headers to include MINIX stuff */
#define _SYSTEM            1	/* tell headers that this is the kernel */

#include <minix/config.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <lib.h>
#include <timers.h>

#include <minix/callnr.h>
#include <minix/type.h>
#include <minix/const.h>
#include <minix/com.h>
#include <minix/syslib.h>
#include <minix/sysutil.h>
#include <minix/vfsif.h>
#include <minix/endpoint.h>
#include <minix/sysinfo.h>
#include <minix/u64.h>
#include <minix/sysinfo.h>
#include <minix/type.h>
#include <minix/ipc.h>

#include <sys/time.h>
#include <sys/times.h>
#include <sys/types.h>
#include <sys/stat.h>


#include <minix/vtreefs.h>
#include "devman.h"
#include "proto.h"

static void init_hook(void) {
	static int first = 1;
	
	if (first) {
		devman_init_devices();
		first = 0;
	}
}


static int message_hook (message *m)
{
	switch (m->m_type) {
		case DEVMAN_ADD_DEV:
			return do_add_device(m);
		case DEVMAN_DEL_DEV:
			return do_del_device(m);
		case DEVMAN_BIND:
			return do_bind_device(m);
		case DEVMAN_UNBIND:
			return do_unbind_device(m);
		default: return -1;
	}
}

static int 
read_hook
(struct inode *inode, off_t offset, char **ptr, size_t *len, cbdata_t cbdata)
{
	struct devman_inode *d_inode = (struct devman_inode *) cbdata;

	return d_inode->read_fn(ptr, len, offset, d_inode->data);
}


int main (int argc, char* argv[])
{

	struct fs_hooks hooks;
	struct inode_stat root_stat;

	/* fill in the hooks */
	memset(&hooks, 0, sizeof(hooks));
	hooks.init_hook 	= init_hook;
	hooks.read_hook 	= read_hook; /* read will never be called */
	hooks.message_hook 	= message_hook;	/* handle the ds_update call */

	root_stat.mode 	= S_IFDIR | S_IRUSR | S_IRGRP | S_IROTH;
	root_stat.uid 	= 0;
	root_stat.gid 	= 0;
	root_stat.size 	= 0;
	root_stat.dev 	= NO_DEV;

	/* limit the number of indexed entries */
	start_vtreefs(&hooks, 1024 , &root_stat, 0);
	return 0;
}

