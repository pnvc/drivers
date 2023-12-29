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

struct scull_dev {
	dev_t dev;
	struct scull_qset *data;
	int quantum;
	int qset;
	unsigned long size;
	unsigned int access_key;
	struct semaphore sem;
	struct cdev cdev;
};

static int reg_dev(void);
static void reg_cdev(void);
static int scull_open(struct inode *, struct file *);
static int scull_release(struct inode *, struct file *);
static int scull_trim(struct scull_dev *);
static ssize_t scull_read(struct file *filp, char __user *buf,
	size_t count, loff_t *offp);
static ssize_t scull_write(struct file *filp, const char __user *buf,
	size_t count, loff_t *offp);
static struct scull_qset* scull_follow(struct scull_dev *, int);
static loff_t scull_llseek(struct file*, loff_t, int);


#endif /* _SCULL_MAIN_H */
