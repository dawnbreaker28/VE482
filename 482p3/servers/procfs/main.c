/* ProcFS - main.c - by Alen Stojanov and David van Moolenbroek */

#include "inc.h"
#include "cpuinfo.h"

static void init_hook(void);

/* The hook functions that will be called by VTreeFS. */
static struct fs_hooks hooks = {
	init_hook,
	NULL,		/* cleanup_hook */
	lookup_hook,
	getdents_hook,
	read_hook,
	rdlink_hook,
	NULL		/* message_hook */
};

/*===========================================================================*
 *				construct_tree				     *
 *===========================================================================*/
static void construct_tree(struct inode *dir, struct file *files)
{
	/* Construct a tree of static files from a null-terminated array of
	 * file structures, recursively creating directories which have their
	 * associated data point to child file structures.
	 */
	struct file *file;
	struct inode *node;
	struct inode_stat stat;

	stat.uid = SUPER_USER;
	stat.gid = SUPER_USER;
	stat.size = 0;
	stat.dev = NO_DEV;

	for (file = files; file->name != NULL; file++) {
		stat.mode = file->mode;

		node = add_inode(dir, file->name, NO_INDEX, &stat, (index_t) 0,
			(cbdata_t) file->data);

		assert(node != NULL);

		if (S_ISDIR(file->mode))
			construct_tree(node, (struct file *) file->data);
	}
}

/*===========================================================================*
 *				init_hook				     *
 *===========================================================================*/
static void init_hook(void)
{
	/* Initialization hook. Generate the static part of the tree.
	 */
	static int first_time = 1;
	struct inode *root;

	if (first_time) {
		root = get_root_inode();

		construct_tree(root, root_files);

		first_time = 0;
	}
}

/*===========================================================================*
 *				main					     *
 *===========================================================================*/
int main(void)
{
	/* ProcFS entry point.
	 */
	struct inode_stat stat;
	int r;

	/* Initialize some state. If we are incompatible with the kernel, exit
	 * immediately.
	 */
	if ((r = init_tree()) != OK)
		return r;

	/* Properties of the root directory. */
	stat.mode 	= DIR_ALL_MODE;
	stat.uid 	= SUPER_USER;
	stat.gid 	= SUPER_USER;
	stat.size 	= 0;
	stat.dev 	= NO_DEV;

	/* Start VTreeFS. This call does not return. */
	start_vtreefs(&hooks, NR_INODES, &stat, NR_PROCS + NR_TASKS);

	return 0;
}
