#ifndef LDDBUS_H_SENTRY
#define LDDBUS_H_SENTRY

struct ldd_dev {
	char *name;
	struct ldd_drv *drv;
	struct device dev;
};
#define to_ldd_dev(dev) container_of(dev, struct ldd_dev, dev);

extern int register_ldd_dev(struct ldd_dev *);

#endif
