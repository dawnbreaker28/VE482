.if defined(NBSD_LIBC) && (${NBSD_LIBC} == "yes")
CPPFLAGS+= -D_MINIX -D_NETBSD_SOURCE
.else
CPPFLAGS+= -D_MINIX -D_POSIX_SOURCE
.endif
