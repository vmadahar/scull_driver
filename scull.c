#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>

MODULE_LICENSE("GPL");

#define SCULL_DEVICE_NAME "scull_driver"

typedef struct scull_s
{
	dev_t dev;
	int major;
	int minor;
} scull_t;

scull_t scull;

static int __init scull_init(void)
{
	int result = 0;	
	result = alloc_chrdev_region(&scull.dev, 0, 1, SCULL_DEVICE_NAME);
	if (result)
	{
		printk(KERN_ALERT "Error while registering the device\n");
		return result;
	}
	scull.major = MAJOR(scull.dev);
	scull.minor = MINOR(scull.dev);
	printk("Hello, world!\n");	
	printk("scull_driver major: %u minor: %u dev: %u\n", scull.major, scull.minor,scull.dev);
	return 0;
}

static void __exit scull_exit(void)
{
	printk("Goodbye, cruel world!\n");
	printk("Removing device: %u\n", scull.major);
	unregister_chrdev_region(scull.dev,1);
}

module_init(scull_init);
module_exit(scull_exit);