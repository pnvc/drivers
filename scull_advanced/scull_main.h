#ifndef _SCULL_MAIN_H
#define _SCULL_MAIN_H

#undef PDEBUG
#ifdef SCULL_DEBUG
#	ifdef __KERNEL__
#		define PDEBUG(fmt, ...) printk(KERN_DEBUG "scull: " fmt, ##__VA_ARGS__)
#	else
#		define PDEBUG(fmt, ...) fprintf(stderr, fmt, ##__VA_ARGS__)
#	endif /* __KERNEL__ */
#else
#	define PDEBUG(fmt, args...)
#endif /* SCULL_DEBUG */

struct scull_qset {
	void **data;
	struct scull_qset *next;
};

struct scull_cdev {
	struct scull_qset *data;
	int quantum;
	int qset;
	unsigned long size;
	loff_t general_offset;
	unsigned int access_key;
	struct semaphore sem;
	struct cdev cdev;
};

struct scull_dev {
	dev_t dev;
	struct scull_cdev node[4];
};

static int reg_dev(void);
static void reg_cdev(void);
static int scull_open(struct inode *, struct file *);
static int scull_release(struct inode *, struct file *);
static int scull_trim(void);
static struct scull_qset* scull_follow_for_write(struct scull_cdev *, int item);
static struct scull_qset* scull_follow(struct scull_cdev *, int item);
static ssize_t scull_read(struct file *filp, char __user *buf,
	size_t count, loff_t *offp);
static ssize_t scull_write(struct file *filp, const char __user *buf,
	size_t count, loff_t *offp);
static loff_t scull_llseek(struct file*, loff_t, int);

/* ioctl */
static long ioctl(struct file *, unsigned int, unsigned long);

#endif /* _SCULL_MAIN_H */
