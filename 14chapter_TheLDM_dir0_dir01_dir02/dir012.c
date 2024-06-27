#include <linux/module.h>
#include <linux/init.h>
#include <linux/kobject.h>
#include <linux/sysfs.h>
#include <linux/export.h>

#define DIR012	"dir012"
#define MES	"dir012: "
#define DIR0	"dir0"
#define DIR1	"dir0:1"
#define DIR2	"dir0:2"

					/* DIR0 */
/* declaration and description */
/* main struct with dir0 kobj */
struct dir0 {
	struct kobject kobj;
	int cmd;
};
#define to_dir0(x) container_of(x, struct dir0, kobj)

/* dir0 container with show/store function an struct attribute */
struct dir0_attribute {
	struct attribute attr;
	ssize_t (*show)(struct dir0 *dir0, struct dir0_attribute *attr,
			char *buffer);
	ssize_t (*store)(struct dir0 *dir0, struct dir0_attribute *attr,
			 const char *buffer, size_t count);
};
#define to_dir0_attribute(x) container_of(x, struct dir0_attribute, attr)

/* kobj release */
static void dir0_release(struct kobject *kobj);

/* sysfs show/store */
static ssize_t _dir0_show(struct kobject *kobj, struct attribute *attr,
			  char *buffer);
static ssize_t _dir0_store(struct kobject *kobj, struct attribute *attr,
			   const char *buffer, size_t count);

/* dir0 container sysfs show/store */
static ssize_t dir0_show(struct dir0 *d, struct dir0_attribute *attr,
			  char *buffer);
static ssize_t dir0_store(struct dir0 *d, struct dir0_attribute *attr,
			  const char *buffer, size_t count);

/* description */
static void dir0_release(struct kobject *kobj)
{
	struct dir0 *dir0 = to_dir0(kobj);
	kfree(dir0);
}

static ssize_t _dir0_show(struct kobject *kobj, struct attribute *attr,
			  char *buffer)
{
	struct dir0_attribute *d0_attr;
	struct dir0 *d0;

	d0_attr = to_dir0_attribute(attr);
	d0 = to_dir0(kobj);

	if (!d0_attr->show)
		return -EIO;

	return d0_attr->show(d0, d0_attr, buffer);
}
static ssize_t _dir0_store(struct kobject *kobj, struct attribute *attr,
			   const char *buffer, size_t count)
{
	struct dir0_attribute *d0_attr;
	struct dir0 *d0;

	d0_attr = to_dir0_attribute(attr);
	d0 = to_dir0(kobj);

	if (!d0_attr->store)
		return -EIO;

	return d0_attr->store(d0, d0_attr, buffer, count);
}

static ssize_t dir0_show(struct dir0 *d, struct dir0_attribute *attr,
			  char *buffer)
{
	return sysfs_emit(buffer, "%d\n", d->cmd);
}

static ssize_t dir0_store(struct dir0 *d, struct dir0_attribute *attr,
			  const char *buffer, size_t count)
{
	int ret;

	ret = kstrtoint(buffer, 10, &d->cmd);
	if (ret < 0)
		return ret;

	return count;
}

static struct sysfs_ops dir0_sysfs_ops = {
	.show = _dir0_show,
	.store = _dir0_store
};

static struct dir0_attribute dir0_attribute =
	__ATTR(file0, 0664, dir0_show, dir0_store);

static struct attribute *dir0_def_attrs[] = {
	&dir0_attribute.attr,
	NULL
};
ATTRIBUTE_GROUPS(dir0_def);

static struct kobj_type dir0_ktype = {
	.release = dir0_release,
	.sysfs_ops = &dir0_sysfs_ops,
	.default_groups = dir0_def_groups
};

static struct dir0 *dir0;
					/* DIR0 */

					/* DIR1 */
/* declaration and description */
struct dir1 {
	struct kobject kobj;
	int file0;
	int file1;
};
#define to_dir1(x) container_of(x, struct dir1, kobj)

/* dir0 container with show/store function an struct attribute */
struct dir1_attribute {
	struct attribute attr;
	ssize_t (*show)(struct dir1 *dir1, struct dir1_attribute *attr,
			char *buffer);
	ssize_t (*store)(struct dir1 *dir1, struct dir1_attribute *attr,
			 const char *buffer, size_t count);
};
#define to_dir1_attribute(x) container_of(x, struct dir1_attribute, attr)

/* kobj release */
static void dir1_release(struct kobject *kobj);

/* sysfs show/store */
static ssize_t _dir1_show(struct kobject *kobj, struct attribute *attr,
			  char *buffer);
static ssize_t _dir1_store(struct kobject *kobj, struct attribute *attr,
			   const char *buffer, size_t count);

/* dir0 container sysfs show/store */
static ssize_t dir1_show(struct dir1 *d, struct dir1_attribute *attr,
			  char *buffer);
static ssize_t dir1_store(struct dir1 *d, struct dir1_attribute *attr,
			  const char *buffer, size_t count);
static ssize_t dir1_file1_store(struct dir1 *d, struct dir1_attribute *attr,
				const char *buffer, size_t count);

/* description */
static void dir1_release(struct kobject *kobj)
{
	struct dir1 *dir1 = to_dir1(kobj);
	kfree(dir1);
}

static ssize_t _dir1_show(struct kobject *kobj, struct attribute *attr,
			  char *buffer)
{
	struct dir1_attribute *d1_attr;
	struct dir1 *d1;

	d1_attr = to_dir1_attribute(attr);
	d1 = to_dir1(kobj);

	if (!d1_attr->show)
		return -EIO;

	return d1_attr->show(d1, d1_attr, buffer);
}
static ssize_t _dir1_store(struct kobject *kobj, struct attribute *attr,
			   const char *buffer, size_t count)
{
	struct dir1_attribute *d1_attr;
	struct dir1 *d1;

	d1_attr = to_dir1_attribute(attr);
	d1 = to_dir1(kobj);

	if (!d1_attr->store)
		return -EIO;

	return d1_attr->store(d1, d1_attr, buffer, count);
}

static ssize_t dir1_show(struct dir1 *d, struct dir1_attribute *attr,
			  char *buffer)
{
	int var;

	if (strcmp(attr->attr.name, "file0") == 0)
		var = d->file0;
	else
		var = d->file1;

	return sysfs_emit(buffer, "%d\n", var);
}

static ssize_t dir1_store(struct dir1 *d, struct dir1_attribute *attr,
			  const char *buffer, size_t count)
{
	int ret, var;

	ret = kstrtoint(buffer, 10, &var);
	if (ret < 0)
		return ret;

	if (strcmp(attr->attr.name, "file0") == 0)
		d->file0 = var;
	else
		d->file1 = var;

	return count;
}

static ssize_t dir1_file1_store(struct dir1 *d, struct dir1_attribute *attr,
				const char *buffer, size_t count)
{
	int ret;

	ret = kstrtoint(buffer, 10, &d->file1);
	if (ret < 0)
		return ret;

	return count;
}

static struct sysfs_ops dir1_sysfs_ops = {
	.show = _dir1_show,
	.store = _dir1_store
};

static struct dir1_attribute dir1_file0_attribute =
	__ATTR(file0, 0664, dir1_show, dir1_store);
static struct dir1_attribute dir1_file1_attribute =
	__ATTR(file1, 0664, dir1_show, dir1_file1_store);

static struct attribute *dir1_def_attrs[] = {
	&dir1_file0_attribute.attr,
	&dir1_file1_attribute.attr,
	NULL
};
ATTRIBUTE_GROUPS(dir1_def);

static struct kobj_type dir1_ktype = {
	.release = dir1_release,
	.sysfs_ops = &dir1_sysfs_ops,
	.default_groups = dir1_def_groups
};

static struct dir1 *dir1;
					/* DIR1 */

					/* DIR2 */
					/* DIR2 */

					/* KSET */
static int dir012_uevent_filter(const struct kobject *kobj)
{
	const struct kobj_type *kt = get_ktype(kobj);
	pr_info(MES"%s\n", kt->default_groups[0]->name);
	return 1;
}
static struct kset_uevent_ops dir012_kset_uevent_ops = {
	.filter = dir012_uevent_filter
};
struct kset *dir012_kset;
static struct kset *get_dir012_kset(void)
{
	return dir012_kset;
}
EXPORT_SYMBOL_GPL(dir012_kset);
					/* KSET */

static int __init dir012_init(void)
{
					/* KSET */
	dir012_kset = kset_create_and_add("dir012_kset", (const struct kset_uevent_ops *)&dir012_kset_uevent_ops, NULL);
	if (!dir012_kset)
		return -ENOMEM;
					/* KSET */
					/* DIR0 */
	dir0 = kzalloc(sizeof(*dir0), GFP_KERNEL);
	if (!dir0)
		return -ENOMEM;

	dir0->kobj.kset = dir012_kset;

	if (kobject_init_and_add(&dir0->kobj, &dir0_ktype, NULL, DIR0)) {
		kobject_put(&dir0->kobj);
		return -EFAULT;
	}
					/* DIR0 */

					/* DIR1 */
	dir1 = kzalloc(sizeof(*dir1), GFP_KERNEL);
	if (!dir1) {
		kobject_put(&dir0->kobj);
		return -ENOMEM;
	}

	if (kobject_init_and_add(&dir1->kobj, &dir1_ktype, &dir0->kobj, DIR1)) {
		kobject_put(&dir1->kobj);
		kobject_put(&dir0->kobj);
		return -EFAULT;
	}
					/* DIR1 */

					/* DIR2 */
					/* DIR2 */

	pr_info(MES"inited\n");

	return 0;
}

static void __exit dir012_exit(void)
{
	kobject_put(&dir1->kobj);
	kobject_put(&dir0->kobj);
	kset_unregister(dir012_kset);

	pr_info(MES"exited\n");
}

module_init(dir012_init);
module_exit(dir012_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("nclud");
MODULE_DESCRIPTION("chapter 14, try eirarchy dir0->(dir0:1 | dir0:2)");
MODULE_VERSION("0.0.0.1");
