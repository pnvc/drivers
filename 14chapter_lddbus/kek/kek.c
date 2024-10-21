#include <linux/module.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/slab.h>
#include <linux/dma-mapping.h>

#include "../lddbus.h"

#define KEK "kek"
#define KEKM "kek: "
#define SNL "%s\n"

static char v[] = "000.000.000.034";
static char name[] = "kek";

struct kek_dev {
	dma_addr_t dmabuf;
	void *dmabuf_virt;
	char *buf;
	char *msg;
	struct ldd_dev ldev;
	struct device class_dev;
};
#define to_kek_dev(dev) container_of(dev, struct kek_dev, ldev)
#define to_kek_dev_from_class_dev(dev) container_of(dev, struct kek_dev, class_dev)

static ssize_t kek_show_ver(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct ldd_dev *ld = to_ldd_dev(dev);
	struct kek_dev *kd = to_kek_dev(ld);
	return snprintf(buf, PAGE_SIZE, "%s\n", kd->msg);
}
static DEVICE_ATTR(ver, S_IRUGO, kek_show_ver, NULL);

static ssize_t kek_class_set_ver(struct device *dev, struct device_attribute *attr, const char *buf, size_t buf_size)
{
	return (ssize_t)strncpy(v, buf, strlen(v));
}
static ssize_t kek_class_show_ver(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct kek_dev *kd = to_kek_dev_from_class_dev(dev);
	return snprintf(buf, PAGE_SIZE, "%s\n", kd->msg);
}
static DEVICE_ATTR(version, 0664, kek_class_show_ver, kek_class_set_ver);

static struct kek_dev kek;

static int register_kek_dev(struct kek_dev *keke)
{
	int err = 0;

	keke->ldev.name = name;
	keke->msg = v;

	err = register_ldd_dev(&keke->ldev);
	if (err)
		return err;


	err = device_create_file(&keke->ldev.dev, &dev_attr_ver);
	if (err)
		pr_info(KEKM SNL, "failed create kek device version file");

	keke->class_dev.init_name = "kek_class";
	if (ldd_class_device_register(&kek.class_dev)) {
		if (err)
			device_remove_file(&keke->ldev.dev, &dev_attr_ver);
		device_unregister(&keke->ldev.dev);
		return -EFAULT;
	}

	if (device_create_file(&keke->class_dev, &dev_attr_version))
		pr_info(KEKM SNL, "failed create kek_class device set version file");

	return 0;
}

static int __init kek_init(void)
{
	int retval;
	retval = register_kek_dev(&kek);
	if (retval)
		return retval;
	kek.buf = kmalloc(PAGE_SIZE, GFP_KERNEL);
	if (!kek.buf) {
		device_remove_file(&kek.ldev.dev, &dev_attr_ver);
		device_unregister(&kek.ldev.dev);
		device_remove_file(&kek.class_dev, &dev_attr_version);
		device_unregister(&kek.class_dev);
		pr_warn("kek: fail kmalloc init\n");
		return -ENOMEM;
	}

	kek.dmabuf_virt = dma_alloc_coherent(&kek.ldev.dev, PAGE_SIZE*2,
			&kek.dmabuf, GFP_KERNEL);
	
	if (!kek.dmabuf_virt) {
		pr_warn("kek: fail dma_alloc_coherent\n");
		kfree(kek.buf);
		device_remove_file(&kek.ldev.dev, &dev_attr_ver);
		device_unregister(&kek.ldev.dev);
		device_remove_file(&kek.class_dev, &dev_attr_version);
		device_unregister(&kek.class_dev);
		return -ENOMEM;
	}

	pr_info("kek: kmalloc: %px\ndmabuf_virt: %px\ndmabuf: %llu\n", kek.buf,
			kek.dmabuf_virt, kek.dmabuf);

	pr_info(KEKM SNL, "init");
	return 0;
}

static void __exit kek_exit(void)
{
	pr_info(KEKM SNL, "exit");
	kfree(kek.buf);
	dma_free_coherent(&kek.ldev.dev, PAGE_SIZE*2, kek.dmabuf_virt,
			kek.dmabuf);
	device_remove_file(&kek.ldev.dev, &dev_attr_ver);
	device_unregister(&kek.ldev.dev);

	device_remove_file(&kek.class_dev, &dev_attr_version);
	device_unregister(&kek.class_dev);
}

module_init(kek_init);
module_exit(kek_exit);

MODULE_AUTHOR("ogokto");
MODULE_DESCRIPTION("kek device for the lddbus");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.0.0.1");
