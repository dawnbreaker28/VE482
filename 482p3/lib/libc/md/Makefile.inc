#	$NetBSD: Makefile.inc,v 1.7 2005/09/24 20:51:14 elad Exp $

.include <bsd.own.mk>

# MD4/MD5 sources
.PATH: ${ARCHDIR}/md ${.CURDIR}/md

SRCS+=	md4c.c md5c.c md4hl.c md5hl.c

MAN+=	md4.3 md5.3

MLINKS+=md4.3 MD4Init.3 md4.3 MD4Update.3 md4.3 MD4Final.3
MLINKS+=md4.3 MD4End.3  md4.3 MD4File.3   md4.3 MD4Data.3
MLINKS+=md5.3 MD5Init.3 md5.3 MD5Update.3 md5.3 MD5Final.3
MLINKS+=md5.3 MD5End.3  md5.3 MD5File.3   md5.3 MD5Data.3

CLEANFILES+=	md[45]hl.c md[45].3

.if ${MKMAN} != "no"
md4.3: mdX.3
	sed -e 's/mdX/md4/g' -e 's/MDX/MD4/g' $> > $@
	cat ${>:H}/md4.copyright >> $@

md5.3: mdX.3
	sed -e 's/mdX/md5/g' -e 's/MDX/MD5/g' $> > $@
	cat ${>:H}/md5.copyright >> $@
.endif
