#include <linux/module.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/slab.h>
#include <linux/dma-mapping.h>
#include <linux/dmapool.h>

#include "../lddbus.h"

#define KEK "kek"
#define KEKM "kek: "
#define SNL "%s\n"

static char v[] = "000.000.000.034";
static char name[] = "kek";

struct kek_dev {
	char *buf;
	char *msg;
	struct ldd_dev ldev;
	struct device class_dev;
};
#define to_kek_dev(dev) container_of(dev, struct kek_dev, ldev)
#define to_kek_dev_from_class_dev(dev) container_of(dev, struct kek_dev, class_dev)

static struct kek_dev kek;

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

	char *buf = kmalloc(PAGE_SIZE, GFP_KERNEL);
	if (buf) {
		dma_addr_t bus = dma_map_single(&kek.ldev.dev, buf, 123,
				DMA_TO_DEVICE);

		pr_info("kek: km: %px, bus: %llu\n", buf, bus);
		if (bus)
			dma_unmap_single(&kek.ldev.dev, bus, 123, DMA_NONE);
		kfree(buf);
	}

/*
	struct dma_pool *dp = 0;
	dp = dma_pool_create("dm_pool", &kek.ldev.dev, 123, 8, 0);
	if (IS_ERR_OR_NULL(dp)) {
		pr_warn("kek: fail dma_pool_create\n");
		kfree(kek.buf);
		device_remove_file(&kek.ldev.dev, &dev_attr_ver);
		device_unregister(&kek.ldev.dev);
		device_remove_file(&kek.class_dev, &dev_attr_version);
		device_unregister(&kek.class_dev);
		return PTR_ERR(dp);
	}

	dma_addr_t bus_addr1, bus_addr2;
	void *addr1 = dma_pool_alloc(dp, GFP_KERNEL, &bus_addr1); 

	if (!addr1) {
		pr_warn("kek: fail dma pool alloc: %lu\n", PTR_ERR(addr1));
	}

	pr_info("kek: kmalloc: %px\nkek: dma_pool: %px\nkek: addr: %px\n\
kek: bus_addr: %llu\n",
			kek.buf, dp, addr1, bus_addr1);

	dma_pool_destroy(dp);
*/ // NOT WORKING
	/*
	void *addr;
	dma_addr_t bus_addr;
	u64 dma_mask = DMA_BIT_MASK(24);
	retval = dma_set_mask_and_coherent(&kek.ldev.dev, dma_mask);
	if (retval) {
		pr_info("kek: %d\n", retval);
	}
	kek.ldev.dev.dma_mask = &dma_mask;
	addr = dma_alloc_coherent(&kek.ldev.dev, PAGE_SIZE*2,
			&bus_addr, GFP_KERNEL);
	
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
			addr, bus_addr);

	dma_free_coherent(&kek.ldev.dev, PAGE_SIZE*2, addr, bus_addr);
*/ // noT WORK
	pr_info(KEKM SNL, "init");
	return 0;
}

static void __exit kek_exit(void)
{
	pr_info(KEKM SNL, "exit");
	kfree(kek.buf);
	//dma_free_coherent(&kek.ldev.dev, PAGE_SIZE*2, kek.dmabuf_virt,
	//		kek.dmabuf); // not work
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
