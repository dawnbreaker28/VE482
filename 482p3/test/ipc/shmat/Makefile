# Makefile for the tests

CC = exec cc
CFLAGS = -Wall -D_MINIX -D_POSIX_SOURCE -D_NETBSD_SOURCE=1 -I../lib/

PROG =	shmat01 shmat02 shmat03

all: $(PROG)

$(PROG): ../libipc.a
	$(CC) $(CFLAGS) -o $@ $@.c ../libipc.a

clean:
	rm -f *.o $(PROG)

test:
	sh ./test.sh

shmat01: shmat01.c
shmat02: shmat02.c
shmat03: shmat03.c
