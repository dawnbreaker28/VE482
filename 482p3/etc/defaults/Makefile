#	$NetBSD: Makefile,v 1.5 2011/08/22 20:48:38 jym Exp $

.include <bsd.own.mk>

.if !defined(__MINIX)
CONFIGFILES=	daily.conf monthly.conf security.conf weekly.conf
.else
CONFIGFILES=	minix.rc.conf
.endif # !defined(__MINIX)
FILESDIR=	/etc/defaults
FILESMODE=	${NONBINMODE}

# Manage arch-specific rc.conf(5) file
CONFIGFILES+=	rc_conf
FILESNAME_rc_conf=	rc.conf
FILESBUILD_rc_conf=	yes

# If present, rc.conf.append is added to the end of the default rc.conf file
RCCONF_SRCS=	${.CURDIR}/rc.conf
.if exists(../etc.${MACHINE}/rc.conf.append)
RCCONF_SRCS+=	${.CURDIR}/../etc.${MACHINE}/rc.conf.append
.endif

rc_conf: ${RCCONF_SRCS}
	${_MKTARGET_CREATE}
	${TOOL_CAT} ${RCCONF_SRCS} > ${.TARGET}

.include <bsd.prog.mk>
