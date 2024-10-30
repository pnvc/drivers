#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h> /* container_of */
#include <linux/kobject.h>

static int kobj2_show_int = -123;

static struct kobj_type ktype;
static struct kset *kset;
static struct kobject kobj;
static struct kobject *kobj1, *kobj2, *kobj11;

static void kobj_release(struct kobject *kobj)
{
	pr_info("kkk: %s released\n", kobject_name(kobj));
}

/* kobj2 attrs */
static ssize_t kobj2_show(struct kobject *kobj, struct kobj_attribute *attr,
		char *buf)
{
	return sysfs_emit(buf, "%d", kobj2_show_int);
}

static ssize_t kobj22_store(struct kobject *kobj, struct kobj_attribute *attr,
		const char *buf, size_t size)
{
	int err;

	err = kstrtoint(buf, 10, &kobj2_show_int);
	if (err)
		return err;

	return size;
}

static struct kobj_attribute kobj2_attr =
	__ATTR_RO(kobj2);

static struct kobj_attribute kobj22_attr =
	__ATTR_WO(kobj22);

static struct attribute *attrs[] = {
	&kobj2_attr.attr,
	&kobj22_attr.attr,
	NULL
};

static struct attribute_group attr_group = {
	.attrs = attrs
};

/* kset ops */
static int kset_filter(const struct kobject *kobj)
{
	/* to prevent kobj userspace uevent return 0 at him
	if (!strcmp(kobject_name(kobj), "kobj2"))
		return 0;
	*/
	return 1;
}
static const char *pesos = "pesos";
static const char* kset_name(const struct kobject *kobj)
{
	//return kobject_name(kobj);
	return pesos;
}

static int kset_uevent(const struct kobject *kobj, struct kobj_uevent_env *env)
{
	pr_info("kkk: [%s] uevent\n", kobject_name(kobj));
	pr_info("kkk: %s\n", env->argv[0]);
	return 0;
}

static struct kset_uevent_ops kset_ops = {
	.filter = kset_filter,
	.name = kset_name,
	.uevent = kset_uevent
};

static int __init kkk_init(void)
{
	int err;
	/* create ktype */
	ktype.release = kobj_release;

	/* create kset */
	kset = kset_create_and_add("kset", &kset_ops, NULL);
	if (IS_ERR_OR_NULL(kset)) {
		pr_err("kkk: fail kset create, %ld\n", PTR_ERR(kset));
		return -1;
	}

	/* init and add kobject */
	kobject_init(&kobj, &ktype);
	kobj.kset = kset;
	err = kobject_add(&kobj, NULL, "%s", "kobj");
	if (err) {
		kobject_put(&kobj); /* here need it becouse kobject_init gets */
		pr_err("kkk: fail kobj add, err: %d, file: %s, line :%d\n",
				err, __FILE__, __LINE__);
		return err;
	}

	/* uevent */
	kobj1 = kobject_create_and_add("kobj1", &kobj); /* here and below
							   need check error */
	kobj2 = kobject_create_and_add("kobj2", &kobj);
	err = sysfs_create_group(kobj2, &attr_group);
	if (err) {
		pr_info("kkk: do reboot and check what wrong :)\n");
		return err;
	}
	kobj11 = kobject_create_and_add("kobj11", kobj1);

	err = kobject_uevent(&kobj, KOBJ_ADD); /* return value from
						  kset uevent func */
	pr_info("kkk: %d\n", err);
	kobject_uevent(kobj1, KOBJ_ADD);
	kobject_uevent(kobj2, KOBJ_ADD);
	kobject_uevent(kobj11, KOBJ_ADD);

	pr_info("kkk: inited\n");
	return 0;
}

static void __exit kkk_exit(void)
{
	/*
	 * kobject_del(&kobj); - call some where to explicity call release
	 * function of ktype, but do not kobject_put +- */
	kobject_put(&kobj);
	kobject_put(kobj1);
	kobject_put(kobj2);
	kobject_put(kobj11);
	kset_unregister(kset);
	pr_info("kkk: exited\n");
}

module_init(kkk_init);
module_exit(kkk_exit);

MODULE_AUTHOR("nix4n");
MODULE_DESCRIPTION("kobj ktype kset");
MODULE_VERSION("0.0.0.1");
MODULE_LICENSE("GPL");
