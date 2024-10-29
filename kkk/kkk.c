#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h> /* container_of */
#include <linux/kobject.h>

static struct kobj_type ktype;
static struct kset kset;
static struct kobject kobj;

static void kobj_release(struct kobject *kobj)
{
	pr_info("kkk: %s released\n", kobject_name(kobj));
}

static int __init kkk_init(void)
{
	int err;
	/* create ktype */
	ktype.release = kobj_release;

	/* init and add kobject */
	kobject_init(&kobj, &ktype);
	kobj.kset = NULL;
	err = kobject_add(&kobj, NULL, "%s", "kobj");
	if (err) {
		pr_err("kkk: fail kobj add, err: %d, file: %s, line :%d\n",
				err, __FILE__, __LINE__);
		return err;
	}

	/* uevent */
	kobject_uevent(&kobj, KOBJ_ADD);

	pr_info("kkk: inited\n");
	return 0;
}

static void __exit kkk_exit(void)
{
	kobject_put(&kobj);
	pr_info("kkk: exited\n");
}

module_init(kkk_init);
module_exit(kkk_exit);

MODULE_AUTHOR("nix4n");
MODULE_DESCRIPTION("kobj ktype kset");
MODULE_VERSION("0.0.0.1");
MODULE_LICENSE("GPL");
