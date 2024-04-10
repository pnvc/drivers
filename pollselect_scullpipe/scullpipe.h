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
	struct file_operations fops;
	struct class *dev_class;
};

static int reg_dev(void);
static int reg_cdev(void);
static int create_class_and_node(void);
static void init_sema_and_queue(void);
static int kmalloc_buf(void);

static int param_set_bufsize(const char *, const struct kernel_param *);

static int spacefree(struct scullpipe *);
static int getwritespace(struct scullpipe *, struct file *);

static int sp_open(struct inode *, struct file *);
static int sp_release(struct inode *, struct file *);
static ssize_t sp_read(struct file *, char __user *, size_t, loff_t *);
static ssize_t sp_write(struct file *, const char __user *, size_t, loff_t *);

static long ioctl(struct file *, unsigned int, unsigned long);

static unsigned int sp_poll(struct file *, poll_table *);

static int sp_fasync(int, struct file *, int);

#endif
