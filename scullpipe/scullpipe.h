#ifndef SCULLPIPE_H
#define SCULLPIPE_H

struct scullpipe {
	wait_queue_head_t inq, outq;
	char *buf, *end;
	int bufsize;
	char *rp, *wp;
	int nreaders, nwriters;
	struct fasync_struct *async_queue;
	struct semaphore sem;
	dev_t dev;
	struct cdev cdev;
};

static int reg_dev(void);
static int reg_cdev(void);

static int set_bufsize(const char *, const struct kernel_param *);

#endif
