#include <linux/module.h>
#include <linux/init.h>
#include <linux/kobject.h>
#include <linux/sysfs.h>

#define MES	"dir3: "
#define DIR3	"dir3"

					/* DIR3 */
/* declaration and description */
/* main struct with dir3 kobj */
struct dir3 {
	struct kobject kobj;
	int cmd;
};
#define to_dir3(x) container_of(x, struct dir3, kobj)

/* dir3 container with show/store function an struct attribute */
struct dir3_attribute {
	struct attribute attr;
	ssize_t (*show)(struct dir3 *dir3, struct dir3_attribute *attr,
			char *buffer);
	ssize_t (*store)(struct dir3 *dir3, struct dir3_attribute *attr,
			 const char *buffer, size_t count);
};
#define to_dir3_attribute(x) container_of(x, struct dir3_attribute, attr)

/* kobj release */
static void dir3_release(struct kobject *kobj);

/* sysfs show/store */
static ssize_t _dir3_show(struct kobject *kobj, struct attribute *attr,
			  char *buffer);
static ssize_t _dir3_store(struct kobject *kobj, struct attribute *attr,
			   const char *buffer, size_t count);

/* dir3 container sysfs show/store */
static ssize_t dir3_show(struct dir3 *d, struct dir3_attribute *attr,
			  char *buffer);
static ssize_t dir3_store(struct dir3 *d, struct dir3_attribute *attr,
			  const char *buffer, size_t count);

/* description */
static void dir3_release(struct kobject *kobj)
{
	struct dir3 *dir3 = to_dir3(kobj);
	kfree(dir3);
}

static ssize_t _dir3_show(struct kobject *kobj, struct attribute *attr,
			  char *buffer)
{
	struct dir3_attribute *d3_attr;
	struct dir3 *d3;

	d3_attr = to_dir3_attribute(attr);
	d3 = to_dir3(kobj);

	if (!d3_attr->show)
		return -EIO;

	return d3_attr->show(d3, d3_attr, buffer);
}
static ssize_t _dir3_store(struct kobject *kobj, struct attribute *attr,
			   const char *buffer, size_t count)
{
	struct dir3_attribute *d3_attr;
	struct dir3 *d3;

	d3_attr = to_dir3_attribute(attr);
	d3 = to_dir3(kobj);

	if (!d3_attr->store)
		return -EIO;

	return d3_attr->store(d3, d3_attr, buffer, count);
}

static ssize_t dir3_show(struct dir3 *d, struct dir3_attribute *attr,
			  char *buffer)
{
	return sysfs_emit(buffer, "%d\n", d->cmd);
}

static ssize_t dir3_store(struct dir3 *d, struct dir3_attribute *attr,
			  const char *buffer, size_t count)
{
	int ret;

	ret = kstrtoint(buffer, 10, &d->cmd);
	if (ret < 0)
		return ret;

	return count;
}

static struct sysfs_ops dir3_sysfs_ops = {
	.show = _dir3_show,
	.store = _dir3_store
};

static struct dir3_attribute dir3_attribute =
	__ATTR(file0, 0664, dir3_show, dir3_store);

static struct attribute *dir3_def_attrs[] = {
	&dir3_attribute.attr,
	NULL
};
ATTRIBUTE_GROUPS(dir3_def);

static struct kobj_type dir3_ktype = {
	.release = dir3_release,
	.sysfs_ops = &dir3_sysfs_ops,
	.default_groups = dir3_def_groups
};

static struct dir3 *dir3;
					/* DIR3 */
extern struct kset *dir012_kset;

static int __init dir3_init(void)
{
					/* DIR3 */
	dir3 = kzalloc(sizeof(*dir3), GFP_KERNEL);
	if (!dir3)
		return -ENOMEM;

	if (!dir012_kset) {
		pr_info(MES"need dir012_kset to be defined\n");
		return -EFAULT;
	}

	dir3->kobj.kset = dir012_kset;

	if (kobject_init_and_add(&dir3->kobj, &dir3_ktype, NULL, DIR3)) {
		kobject_put(&dir3->kobj);
		return -EFAULT;
	}

	kobject_uevent(&dir3->kobj, KOBJ_ADD);
					/* DIR3 */

	pr_info(MES"inited\n");

	return 0;
}

static void __exit dir3_exit(void)
{
	kobject_put(&dir3->kobj);

	pr_info(MES"exited\n");
}

module_init(dir3_init);
module_exit(dir3_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("nclud");
MODULE_DESCRIPTION("chapter 14, try add kobj to kset for uevent wait");
MODULE_VERSION("0.0.0.1");
