#include <linux/module.h>
#include <linux/init.h>
#include <linux/assoc_array.h>

static unsigned long ar_get_key_chunk(const void *index_key, int level);
static unsigned long ar_get_object_key_chunk(const void *object, int level);
static bool ar_compare_object(const void *object, const void *index_key);
static int ar_diff_objects(const void *object, const void *index);
static void ar_free_object(void *object);

static struct assoc_array ar;
static struct assoc_array_edit *are;
static const struct assoc_array_ops arops = {
	.get_key_chunk = ar_get_key_chunk,
	.get_object_key_chunk = ar_get_object_key_chunk,
	.compare_object = ar_compare_object,
	.diff_objects = ar_diff_objects,
	.free_object = ar_free_object
};

struct sar {
	int a;
	int b;
};

static unsigned long ar_get_key_chunk(const void *index_key, int level)
{
	pr_info("assarr: get key chunk\n");
	return 1;
}

static unsigned long ar_get_object_key_chunk(const void *object, int level)
{
	pr_info("assarr: get object key chunk\n");
	return 1;
}

static bool ar_compare_object(const void *object, const void *index_key)
{
	pr_info("assarr: compare object\n");
	return true;
}

static int ar_diff_objects(const void *object, const void *index)
{
	pr_info("assarr: diff objects\n");
	return 1;
}

static void ar_free_object(void *object)
{
	kfree(object);
	pr_info("assarr: free object\n");
	return;
}

static char *k = "pipec";

static int __init assarr_init(void)
{
	struct sar *sar0 = kmalloc(sizeof(*sar0), GFP_KERNEL);
	struct sar *sar1 = kmalloc(sizeof(*sar1), GFP_KERNEL);
	struct sar *sar2 = kmalloc(sizeof(*sar2), GFP_KERNEL);
	struct sar *sar3 = kmalloc(sizeof(*sar3), GFP_KERNEL);

	assoc_array_init(&ar);

//	are = assoc_array_insert(&ar, &arops, (const void *)k, (void *)sar0);

	assoc_array_destroy(&ar, &arops);

	kfree(sar0);
	kfree(sar1);
	kfree(sar2);
	kfree(sar3);

	pr_info("assarr: inited\n");
	return 0;
}

static void __exit assarr_exit(void)
{
	pr_info("assarr: exited\n");
}

module_init(assarr_init);
module_exit(assarr_exit);

MODULE_AUTHOR("nx4n");
MODULE_DESCRIPTION("associative array");
MODULE_VERSION("0.0.0.1");
MODULE_LICENSE("GPL");
