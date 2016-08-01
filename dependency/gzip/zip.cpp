/* zip.c -- compress files to the gzip or pkzip format
 * Copyright (C) 1992-1993 Jean-loup Gailly
 * This is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License, see the file COPYING.
 */
#ifdef RCSID
static char rcsid[] = "$Id: zip.c,v 0.17 1993/06/10 13:29:25 jloup Exp $";
#endif

#include <ctype.h>
#include <sys/types.h>

#include "tailor.h"
#include "gzip.h"
#include "crypt.h"

#ifdef HAVE_UNISTD_H
#  include <unistd.h>
#endif
#ifndef NO_FCNTL_H
#  include <fcntl.h>
#endif

local ulg crc;       /* crc on uncompressed file data */
long header_bytes;   /* number of bytes in gzip header */

//ulg deflate();

/* ===========================================================================
 * Deflate in to out.
 * IN assertions: the input and output buffers are cleared.
 *   The variables time_stamp and save_orig_name are initialized.
 */
#ifdef GZIPBUF
int zip(GZBUF in, GZBUF out)
#else
int zip(int in, int out)
#endif
{
    uch  flags = 0;         /* general purpose bit flags */
    ush  attr = 0;          /* ascii/binary flag */
    ush  deflate_flags = 0; /* pkzip -es, -en or -ex equivalent */
	
    ifd = in;
    ofd = out;
    outcnt = 0;
	
    /* Write the header to the gzip file. See algorithm.doc for the format */
	
    method = DEFLATED;
    put_byte(GZIP_MAGIC[0]); /* magic header */
    put_byte(GZIP_MAGIC[1]);
    put_byte(DEFLATED);      /* compression method */
	
    if (save_orig_name) {
		flags |= ORIG_NAME;
    }
    put_byte(flags);         /* general flags */
    put_long(time_stamp);
	
    /* Write deflated file to zip file */
    crc = updcrc(0, 0);
	
    bi_init(out);
    ct_init(&attr, &method);
    lm_init(level, &deflate_flags);
	
    put_byte((uch)deflate_flags); /* extra flags */
    put_byte(OS_CODE);            /* OS identifier */
	
    if (save_orig_name) {
		char *p = basename(ifname); /* Don't save the directory part. */
		do {
			put_char(*p);
		} while (*p++);
    }
    header_bytes = (long)outcnt;
	
    (void)gzip_deflate();
	
#if !defined(NO_SIZE_CHECK) && !defined(RECORD_IO)
	/* Check input size (but not in VMS -- variable record lengths mess it up)
	* and not on MSDOS -- diet in TSR mode reports an incorrect file size)
	*/
    if (ifile_size != -1L && isize != (ulg)ifile_size) {
		Trace((stderr, " actual=%ld, read=%ld ", ifile_size, isize));
		fprintf(stderr, "%s: %s: file size changed while zipping\n",
			progname, ifname);
    }
#endif
	
    /* Write the crc and uncompressed size */
    put_long(crc);
    put_long(isize);
    header_bytes += 2*sizeof(long);
	
    flush_outbuf();
    return OK;
}


/* ===========================================================================
 * Read a new buffer from the current input file, perform end-of-line
 * translation, and update the crc and input file size.
 * IN assertion: size >= 2 (for end-of-line translation)
 */
int file_read(char *buf, unsigned size)
{
    unsigned len;

    Assert(insize == 0, "inbuf not empty");

#ifdef GZIPBUF
	len = ifd->Read(buf, size);
#else
    len = read_mem(ifd, buf, size);
#endif // GZIPBUF
    if (len == (unsigned)(-1) || len == 0) return (int)len;

    crc = updcrc((uch*)buf, len);
    isize += (ulg)len;
    return (int)len;
}

//Transplant start
// int read_mem(int fd, void *buf, unsigned size)
// {
// 	if (size > in_end - in_ptr)
// 		size = in_end - in_ptr;
// 	
// 	(void)memcpy(buf, in_ptr, size);
// 	
// 	in_ptr += size;
// 	return(size);
// }
// 
// int file_read(char *buf, unsigned size)
// {
// 	unsigned len;
// 	
//     Assert(insize == 0, "inbuf not empty");
// 	
//     len = read_mem(0, (void *)buf, size);
//     if (len == (unsigned)(-1) || len == 0) return (int)len;
// 	
//     isize += (ulg)len;
//     return (int)len;
// }
//Transplant end
