#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>

#define DRIVER_DESC "check device connection"
#define DRIVER_AUTHOR "ygarrot"
#define USB_VENDOR_ID  0xfff0
#define USB_PRODUCT_ID 0xfff0

static int usb_probe(struct usb_interface *interface, const struct usb_device_id *id)
{
	printk(KERN_INFO "Pen drive (%04X:%04X) plugged\n", id->idVendor,
			id->idProduct);
	return 0;
}

static void usb_disconnect(struct usb_interface *interface)
{
	printk(KERN_INFO "Usb drive removed\n");
}

static struct usb_device_id usb_table[] =
{
	{ USB_DEVICE(USB_VENDOR_ID, USB_PRODUCT_ID) },
	{}
};

MODULE_DEVICE_TABLE (usb, usb_table);

static struct usb_driver usb_driver =
{
	.name = "ygarrot table",
	.id_table = usb_table,
	.probe = usb_probe,
	.disconnect = usb_disconnect,
};

static int __init usb_init(void)
{
	int result;

	result = usb_register(&usb_driver);
	if (result)
		printk("usb mod: registering driver failed");
	else
		printk("usb mod: driver registered successfully");
	return result;
}

static void __exit usb_exit(void)
{
	usb_deregister(&usb_driver);
	printk("usb mod: module deregistered");
}

module_init(usb_init);
module_exit(usb_exit);

MODULE_LICENSE("GPL");

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);

MODULE_SUPPORTED_DEVICE("testdevice");
