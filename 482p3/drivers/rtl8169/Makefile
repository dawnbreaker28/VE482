# Makefile for the Realtek RTL8169 ethernet driver (RTL8169)
PROG=	rtl8169
SRCS=	rtl8169.c

FILES=$(PROG).conf
FILESNAME=$(PROG)
FILESDIR= /etc/system.conf.d

DPADD+=	${LIBNETDRIVER} ${LIBSYS} ${LIBTIMERS}
LDADD+=	-lnetdriver -lsys -ltimers

MAN=

BINDIR?= /usr/sbin

CPPFLAGS+=	-I${NETBSDSRCDIR}

.include <minix.service.mk>
