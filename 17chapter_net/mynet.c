#include <linux/module.h>
#include <linux/init.h>

#include <linux/netdevice.h>

struct mynet_priv {
	int a;
	double b;
	char buf[100];
};

static int mynet_open(struct net_device *nd);
static int mynet_stop(struct net_device *nd);
static int mynet_dinit(struct net_device *nd);
static int mynet_xmit(struct sk_buff *skb, struct net_device *nd);

static struct net_device *mynet_devs[2];
static struct net_device_ops mynet_devs_ops = {
	.ndo_open = mynet_open,
	.ndo_stop = mynet_stop,
	.ndo_init = mynet_dinit,
	.ndo_start_xmit = mynet_xmit
};

static void mynet_setup(struct net_device *dev);

static void mynet_setup(struct net_device *dev)
{
	return;
}

static int mynet_open(struct net_device *nd)
{
	pr_info("mynet: open\n");
	return 0;
}
static int mynet_stop(struct net_device *nd)
{
	pr_info("mynet: stop\n");
	return 0;
}
static int mynet_dinit(struct net_device *nd)
{
	pr_info("mynet: dinit\n");
	return 0;
}
static int mynet_xmit(struct sk_buff *skb, struct net_device *nd)
{
	pr_info("mynet: xmit\n");
	dev_kfree_skb(skb);
	return 0;
}

static int __init mynet_init(void)
{
	int i;
	int err;

	mynet_devs[0] = alloc_netdev(sizeof(struct mynet_priv), "mynet%d",
			NET_NAME_UNKNOWN, mynet_setup);
	mynet_devs[1] = alloc_netdev(sizeof(struct mynet_priv), "mynet%d",
			NET_NAME_UNKNOWN, mynet_setup);
	if (!mynet_devs[0] || !mynet_devs[1])
		goto out;

	mynet_devs[0]->netdev_ops = &mynet_devs_ops;
	mynet_devs[1]->netdev_ops = &mynet_devs_ops;

	for (i = 0; i < 2; i++) {
		if ((err = register_netdev(mynet_devs[i]))) {
			pr_warn("mynet: error %i, registering device %s\n",
					err, mynet_devs[i]->name);
			goto out;
		}
	}

	pr_info("mynet: started\n");
	return 0;
out:
	return -1;
}

static void __exit mynet_exit(void)
{
	unregister_netdev(mynet_devs[0]);
	unregister_netdev(mynet_devs[1]);
	pr_info("mynet: finished\n");
}

module_init(mynet_init);
module_exit(mynet_exit);

MODULE_AUTHOR("nx4n");
MODULE_DESCRIPTION("my net");
MODULE_VERSION("driver");
MODULE_LICENSE("GPL");
