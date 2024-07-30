#ifndef LDDBUS_H_SENTRY
#define LDDBUS_H_SENTRY

struct ldd_dev {
	char *name;
	struct ldd_drv *ldrv;
	struct device_driver *drv;
	struct device dev;
};
#define to_ldd_dev(dev) container_of(dev, struct ldd_dev, dev)

struct ldd_drv {
	const char *ver;
	struct module *module;
	struct device_driver drv;
	struct driver_attribute ver_attr;
};
#define to_ldd_drv(drv) container_of(drv, struct ldd_drv, drv)

extern int register_ldd_dev(struct ldd_dev *);
extern int register_ldd_drv(struct ldd_drv *);
extern int ldd_class_device_register(struct device *);

#endif
