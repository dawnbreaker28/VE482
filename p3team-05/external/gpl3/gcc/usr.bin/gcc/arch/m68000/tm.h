/* This file is automatically generated.  DO NOT EDIT! */
/* Generated from: 	NetBSD: mknative-gcc,v 1.58 2011/07/02 13:25:05 mrg Exp  */
/* Generated from: NetBSD: mknative.common,v 1.9 2007/02/05 18:26:01 apb Exp  */

#ifndef GCC_TM_H
#define GCC_TM_H
#define TARGET_CPU_DEFAULT (0)
#ifndef NETBSD_ENABLE_PTHREADS
# define NETBSD_ENABLE_PTHREADS
#endif
#ifndef MOTOROLA
# define MOTOROLA 1
#endif
#ifndef USE_GAS
# define USE_GAS 1
#endif
#ifdef IN_GCC
# include "options.h"
# include "config/m68k/m68k.h"
# include "config/dbxelf.h"
# include "config/elfos.h"
# include "config/netbsd.h"
# include "config/netbsd-elf.h"
# include "config/m68k/netbsd-elf.h"
# include "defaults.h"
#endif
#if defined IN_GCC && !defined GENERATOR_FILE && !defined USED_FOR_TARGET
# include "insn-constants.h"
# include "insn-flags.h"
#endif
#endif /* GCC_TM_H */
