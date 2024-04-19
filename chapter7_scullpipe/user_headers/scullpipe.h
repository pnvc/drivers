#ifndef _SCULLPIPE_H_SENTRY
#define _SCULLPIPE_H_SENTRY

#include <asm/ioctl.h>

/*
 * I dont see the number in the ioctl-number.txt
 * between '|' and 0x80
 */
#define SP_IOC_MAGIC			0x0

/*
 * RESET - set default bufsize
 * SET - through a ptr
 * TELL - through an argument (no ptr arg)
 * GET - through a ptr
 * QUERY - by return value
 * SETGET - set and then get by same ptr
 * TELLQUERY - set through an argument and get prev value
 */

#define SP_IOC_BUFSIZE_RESET 		_IO   (SP_IOC_MAGIC, 0xA0)
#define SP_IOC_BUFSIZE_SET		_IOW  (SP_IOC_MAGIC, 0xA1, int)
#define SP_IOC_BUFSIZE_TELL		_IO   (SP_IOC_MAGIC, 0xA2)
#define SP_IOC_BUFSIZE_GET		_IOR  (SP_IOC_MAGIC, 0xA3, int)
#define SP_IOC_BUFSIZE_QUERY		_IO   (SP_IOC_MAGIC, 0xA4)
#define SP_IOC_BUFSIZE_SETGET		_IOWR (SP_IOC_MAGIC, 0xA5, int)
#define SP_IOC_BUFSIZE_TELLQUIERY	_IO   (SP_IOC_MAGIC, 0xA6)
typedef struct { char x[12]; } b;
#define SP_IOC_TEST _IOW(SP_IOC_MAGIC, 0xA7, b)

#define SP_IOC_MAXNR			0xA6
#define SP_IOC_MINNR			0xA0

#endif /* _SCULLPIPE_H_SENTRY */
