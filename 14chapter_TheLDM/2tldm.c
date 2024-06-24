#include <linux/module.h>
#include <linux/init.h>

/* chapter 14 the LDM */
#include <linux/kobject.h>
#include <linux/sysfs.h>

#define TLDM  "2tldm"
#define TLDMM "2tldm: "

#define to_foo(map) container_of(map, struct foo, kobj)
#define to_bar(map) container_of(map, struct bar, kobj)

struct foo {
	struct kobject kobj;
	int cmd;
};

struct bar {
	struct kobject kobj;
	int cmd;
};

struct foo_attribute {
	struct attribute attr;
	ssize_t (*show)(struct foo *foo, struct foo_attrgibute *foo_attr,
			char *buf);
	ssize_t (*store)(struct foo *foo, struct foo_attribute *foo_attr,
			 const char *buf, size_t count)
};
#define to_foo_attribute(map) container_of(map, struct foo_attribute, attr)

struct bar_attribute {
	struct attribute attr;
	ssize_t (*show)(struct bar *bar, struct bar_attrgibute *bar_attr,
			char *buf);
	ssize_t (*store)(struct bar *bar, struct bar_attribute *bar_attr,
			 const char *buf, size_t count)
};
#define to_bar_attribute(map) conatiner_of(map, struct bar_attribute, attr)

static ssize_t foo_show(struct foo *foo, struct foo_attribute *foo_attr,
			char *buf);
static ssize_t foo_store(struct foo *foo, struct foo_attribute *foo_attr,
			 const char *buf, size_t count);
static ssize_t bar_show(struct bar *bar, struct bar_attribute *bar_attr,
			char *buf);
static ssize_t bar_store(struct bar *bar, struct bar_attribute *bar_attr,
			 const char *buf, size_t count);
static ssize_t _foo_show(struct kobject *kobj, struct attribute *attr,
			 char *buf);
static ssize_t _foo_store(struct kobject *kobj, struct attribute *attr,
			  char *buf, size_t count);
static ssize_t _bar_show(struct kobject *kobj, struct attribute *attr,
			 char *buf);
static ssize_t _bar_store(struct kobject *kobj, struct attribute *attr,
			  char *buf, size_t count);
static void foo_release(struct kobject *kobj);
static void bar_release(struct kobject *kobj);

static struct foo_attribute foo_attribute =
	__ATTR("foo", 0664, foo_show, foo_store);

static struct bar_attribute bar_attribute =
	__ATTR("bar", 0664, bar_show, bar_store);

static struct attribute *foo_def_attrs[] = {
	&foo_attribute.attr,
	NULL
};
ATTRIBUTE_GROUP(foo_def);

static struct attribute *bar_def_attrs[] = {
	&bar_attribute.attr,
	NULL
};
ATTRIBUTE_GROUP(bar_def);

static struct sysfs_ops foo_sysfs_ops = {
	.show = _foo_show,
	.store = _foo_store
};

static struct sysfs_ops bar_sysfs_ops = {
	.show = _bar_show,
	.store = _bar_store
};

static const struct kobj_type foo_ktype = {
	.release = foo_release,
	.default_groups = foo_def_groups
};

static const struct kobj_type bar_ktype = {
	.release = bar_release,
	.default_groups = bar_def_groups
};

static struct kset *foo_kset;

static void foo_release(struct kobject *kobj)
{
	struct foo *foo = to_foo(kobj);
	kfree(foo);
}

static void bar_release(struct kobject *kobj)
{
	struct bar *bar = to_bar(kobj);
	kfree(bar);
}

static int __init tldm_init(void)
{
	struct foo *foo;
	struct bar *bar;
	int err_count = 0;

	foo_kset = kset_create_and_add("foo_kset", NULL, NULL);
	if (!foo_kset)
		return -ENOMEM;

	foo = kzalloc(sizeof(*foo), GFP_KERNEL);
	if (!foo)
		return -ENOMEM;

	bar = kzalloc(sizeof(*bar), GFP_KERNEL);
	if (!bar)
		return -ENOMEM;

	foo->kobj.kset = foo_kset;
	bar->kobj.kset = foo_kset;

	if (kobject_init_and_add(&foo->kobj, &foo_ktype, NULL, "foo")) {
		kobject_put(&foo->kobj);
		err_count++;
	}

	if (kobject_init_and_add(&bar->kobj, &bar_ktype, NULL, "bar")) {
		kobject_put(&bar->kobj);
		err_count++;
	}

	if (err_count)
		return -EFAULT;

	kobject_uevent(&foo->kobj, KOBJ_ADD);
	kobject_uevent(&bar->kobj, KOBJ_ADD);

	pr_info(TLDMM"inited\n");

	return 0;
}

static void __exit tldm_exit(void)
{
	kobject_put(&foo->kobj);
	kobject_put(&bar->kobj);

	pr_info(TLDMM"exited\n");
}

module_init(tldm_init);
module_exit(tldm_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("nclud");
MODULE_DESCRIPTION("chapter 14 The Linux Device Model");
MODULE_VERSION("0.0.0.1");
