/*-
 * Copyright (c) 2003-2007 Tim Kientzle
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR(S) ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR(S) BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "test.h"
__FBSDID("$FreeBSD: head/lib/libarchive/test/test_tar_large.c 201247 2009-12-30 05:59:21Z kientzle $");

#include <errno.h>
#include <stdlib.h>
#include <string.h>

/*
 * This is a somewhat tricky test that verifies the ability to
 * write and read very large entries to tar archives.  It
 * writes entries from 2GB up to 1TB to an archive in memory.
 * The memory storage here carefully avoids actually storing
 * any part of the file bodies, so it runs very quickly and requires
 * very little memory.  If you're willing to wait a few minutes,
 * you should be able to exercise petabyte entries with this code.
 */

/*
 * Each file is built up by duplicating the following block.
 */
static size_t filedatasize;
static void *filedata;

/*
 * We store the archive as blocks of data generated by libarchive,
 * each possibly followed by bytes of file data.
 */
struct memblock {
	struct memblock *next;
	size_t	size;
	void *buff;
	int64_t filebytes;
};

/*
 * The total memory store is just a list of memblocks plus
 * some accounting overhead.
 */
struct memdata {
	int64_t filebytes;
	void *buff;
	struct memblock *first;
	struct memblock *last;
};

/* The following size definitions simplify things below. */
#define KB ((int64_t)1024)
#define MB ((int64_t)1024 * KB)
#define GB ((int64_t)1024 * MB)
#define TB ((int64_t)1024 * GB)

#if ARCHIVE_VERSION_NUMBER < 2000000
static ssize_t	memory_read_skip(struct archive *, void *, size_t request);
#else
static off_t	memory_read_skip(struct archive *, void *, off_t request);
#endif
static ssize_t	memory_read(struct archive *, void *, const void **buff);
static ssize_t	memory_write(struct archive *, void *, const void *, size_t);


static ssize_t
memory_write(struct archive *a, void *_private, const void *buff, size_t size)
{
	struct memdata *private = _private;
	struct memblock *block;

	(void)a;

	/*
	 * Since libarchive tries to behave in a zero-copy manner, if
	 * you give a pointer to filedata to the library, a pointer
	 * into that data will (usually) pop out here.  This way, we
	 * can tell the difference between filedata and library header
	 * and metadata.
	 */
	if ((const char *)filedata <= (const char *)buff
	    && (const char *)buff < (const char *)filedata + filedatasize) {
		/* We don't need to store a block of file data. */
		private->last->filebytes += (int64_t)size;
	} else {
		/* Yes, we're assuming the very first write is metadata. */
		/* It's header or metadata, copy and save it. */
		block = (struct memblock *)malloc(sizeof(*block));
		memset(block, 0, sizeof(*block));
		block->size = size;
		block->buff = malloc(size);
		memcpy(block->buff, buff, size);
		if (private->last == NULL) {
			private->first = private->last = block;
		} else {
			private->last->next = block;
			private->last = block;
		}
		block->next = NULL;
	}
	return ((long)size);
}

static ssize_t
memory_read(struct archive *a, void *_private, const void **buff)
{
	struct memdata *private = _private;
	struct memblock *block;
	ssize_t size;

	(void)a;

	free(private->buff);
	private->buff = NULL;
	if (private->first == NULL) {
		private->last = NULL;
		return (ARCHIVE_EOF);
	}
	if (private->filebytes > 0) {
		/*
		 * We're returning file bytes, simulate it by
		 * passing blocks from the template data.
		 */
		if (private->filebytes > (int64_t)filedatasize)
			size = (ssize_t)filedatasize;
		else
			size = (ssize_t)private->filebytes;
		private->filebytes -= size;
		*buff = filedata;
	} else {
		/*
		 * We need to get some real data to return.
		 */
		block = private->first;
		private->first = block->next;
		size = (ssize_t)block->size;
		if (block->buff != NULL) {
			private->buff = block->buff;
			*buff = block->buff;
		} else {
			private->buff = NULL;
			*buff = filedata;
		}
		private->filebytes = block->filebytes;
		free(block);
	}
	return (size);
}


#if ARCHIVE_VERSION_NUMBER < 2000000
static ssize_t
memory_read_skip(struct archive *a, void *private, size_t skip)
{
	(void)a;  /* UNUSED */
	(void)private; /* UNUSED */
	(void)skip; /* UNUSED */
	return (0);
}
#else
static off_t
memory_read_skip(struct archive *a, void *_private, off_t skip)
{
	struct memdata *private = _private;

	(void)a;

	if (private->first == NULL) {
		private->last = NULL;
		return (0);
	}
	if (private->filebytes > 0) {
		if (private->filebytes < skip)
			skip = (off_t)private->filebytes;
		private->filebytes -= skip;
	} else {
		skip = 0;
	}
	return (skip);
}
#endif

DEFINE_TEST(test_tar_large)
{
	/* The sizes of the entries we're going to generate. */
	static int64_t tests[] = {
		/* Test for 32-bit signed overflow. */
		2 * GB - 1, 2 * GB, 2 * GB + 1,
		/* Test for 32-bit unsigned overflow. */
		4 * GB - 1, 4 * GB, 4 * GB + 1,
		/* 8GB is the "official" max for ustar. */
		8 * GB - 1, 8 * GB, 8 * GB + 1,
		/* Bend ustar a tad and you can get 64GB (12 octal digits). */
		64 * GB - 1, 64 * GB,
		/* And larger entries that require non-ustar extensions. */
		256 * GB, 1 * TB, 0 };
	int i;
	char namebuff[64];
	struct memdata memdata;
	struct archive_entry *ae;
	struct archive *a;
	int64_t  filesize;
	size_t writesize;

	filedatasize = (size_t)(1 * MB);
	filedata = malloc(filedatasize);
	memset(filedata, 0xAA, filedatasize);
	memset(&memdata, 0, sizeof(memdata));

	/*
	 * Open an archive for writing.
	 */
	a = archive_write_new();
	archive_write_set_format_pax_restricted(a);
	archive_write_set_bytes_per_block(a, 0); /* No buffering. */
	archive_write_open(a, &memdata, NULL, memory_write, NULL);

	/*
	 * Write a series of large files to it.
	 */
	for (i = 0; tests[i] != 0; i++) {
		assert((ae = archive_entry_new()) != NULL);
		sprintf(namebuff, "file_%d", i);
		archive_entry_copy_pathname(ae, namebuff);
		archive_entry_set_mode(ae, S_IFREG | 0755);
		filesize = tests[i];

		archive_entry_set_size(ae, filesize);

		assertA(0 == archive_write_header(a, ae));
		archive_entry_free(ae);

		/*
		 * Write the actual data to the archive.
		 */
		while (filesize > 0) {
			writesize = filedatasize;
			if ((int64_t)writesize > filesize)
				writesize = (size_t)filesize;
			assertA((int)writesize
			    == archive_write_data(a, filedata, writesize));
			filesize -= writesize;
		}
	}

	assert((ae = archive_entry_new()) != NULL);
	archive_entry_copy_pathname(ae, "lastfile");
	archive_entry_set_mode(ae, S_IFREG | 0755);
	assertA(0 == archive_write_header(a, ae));
	archive_entry_free(ae);


	/* Close out the archive. */
	assertA(0 == archive_write_close(a));
#if ARCHIVE_VERSION_NUMBER < 2000000
	archive_write_finish(a);
#else
	assertA(0 == archive_write_finish(a));
#endif

	/*
	 * Open the same archive for reading.
	 */
	a = archive_read_new();
	archive_read_support_format_tar(a);
	archive_read_open2(a, &memdata, NULL,
	    memory_read, memory_read_skip, NULL);

	/*
	 * Read entries back.
	 */
	for (i = 0; tests[i] > 0; i++) {
		assertEqualIntA(a, 0, archive_read_next_header(a, &ae));
		sprintf(namebuff, "file_%d", i);
		assertEqualString(namebuff, archive_entry_pathname(ae));
		assert(tests[i] == archive_entry_size(ae));
	}
	assertEqualIntA(a, 0, archive_read_next_header(a, &ae));
	assertEqualString("lastfile", archive_entry_pathname(ae));

	assertEqualIntA(a, ARCHIVE_EOF, archive_read_next_header(a, &ae));

	/* Close out the archive. */
	assertA(0 == archive_read_close(a));
#if ARCHIVE_VERSION_NUMBER < 2000000
	archive_read_finish(a);
#else
	assertA(0 == archive_read_finish(a));
#endif

	free(memdata.buff);
	free(filedata);
}
