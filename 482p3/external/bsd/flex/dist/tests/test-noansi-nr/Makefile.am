# This file is part of flex.

# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:

# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.

# Neither the name of the University nor the names of its contributors
# may be used to endorse or promote products derived from this software
# without specific prior written permission.

# THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE.


FLEX = $(top_builddir)/flex

EXTRA_DIST = scanner.l test.input
CLEANFILES = scanner.c parser.c parser.h $(testname)$(EXEEXT) OUTPUT $(OBJS)
OBJS = scanner.o # parser.o

AM_CPPFLAGS = -I$(srcdir) -I$(top_srcdir) -I$(top_builddir)
#LDFLAGS = $(top_srcdir)/libfl.a 
#YFLAGS = --defines --output=parser.c

testname = test-noansi-nr

scanner.c: $(srcdir)/scanner.l
	$(FLEX) $<

parser.c: $(srcdir)/parser.y
	$(BISON) $(YFLAGS) $<

$(testname)$(EXEEXT): $(OBJS)
	$(CC) -o $@ $(LDFLAGS) $(OBJS) $(LOADLIBES)

test: $(testname)$(EXEEXT)
	./$(testname)$(EXEEXT) < $(srcdir)/test.input

.c.o:
	$(CC) -c -o $@ $(AM_CPPFLAGS) $(CPPFLAGS) $(CFLAGS) $<
