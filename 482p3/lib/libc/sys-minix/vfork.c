#include <sys/cdefs.h>
#include "namespace.h"
#include <lib.h>

#include <unistd.h>

#ifdef __weak_alias
__weak_alias(vfork, __vfork14)
#endif

pid_t vfork()
{
  message m;

  return(_syscall(PM_PROC_NR, FORK, &m));
}
