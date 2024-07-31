#include <linux/module.h>
#include <linux/init.h>
#include <linux/usb.h>

#include "usb_vpd.h"

#define MSG "usb_vpd: "
#define VEND 0x0951
#define PROD 0x1666

// USB
static struct usb_device_id usb_vpd_table[] = {
	{ USB_DEVICE(VEND, PROD) },
	{}
};
MODULE_DEVICE_TABLE(usb, usb_vpd_table);

static int
usb_vpd_probe(struct usb_interface *iface, const struct usb_device_id *id);

static void
usb_vpd_disconnect(struct usb_interface *iface);

static struct usb_driver usb_vpd_drv = {
	.name = "usb_vpd",
	.id_table = usb_vpd_table,
	.probe = usb_vpd_probe,
	.disconnect = usb_vpd_disconnect
};

static int
usb_vpd_probe(struct usb_interface *iface, const struct usb_device_id *id)
{
	pr_info(MSG"probe: device %04X %04X\n",
			id->idVendor, id->idProduct);
	return 0;
}
static void __exit usb_vpd_exit(void);
static void
usb_vpd_disconnect(struct usb_interface *iface)
{
	pr_info(MSG"disconnect\n");
}
// USB

// INIT
static int __init usb_vpd_init(void)
{
	int err;

	pr_info(MSG"started. vendorID=0x%04X productID=0x%04X\n", VEND, PROD);

	err = usb_register(&usb_vpd_drv);
	if (err) {
		pr_info(MSG"Unable register driver\n");
		return err;
	}
	return 0;
}
module_init(usb_vpd_init);

// EXIT
static void __exit usb_vpd_exit(void)
{
	usb_deregister(&usb_vpd_drv);
	pr_info(MSG"exited");
}
module_exit(usb_vpd_exit);

// MODULE INFO
MODULE_AUTHOR("nx4n <theonetwothe@gmail.com>");
MODULE_DESCRIPTION("usb_vpd - usb vendor/product driver determiner");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.0.0.1");
