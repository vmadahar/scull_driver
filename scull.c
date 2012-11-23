#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>

MODULE_LICENSE("GPL");

#define SCULL_DEVICE_NAME "scull_driver"

#define NUM_OF_DEVICES 1

static int scull_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg);
static int scull_open(struct inode *inode, struct file *filp);
static int scull_release(struct inode *inode, struct file *filp);

typedef struct scull_s
{
	dev_t dev;
	int major;
	int minor;
} scull_t;
scull_t scull;

struct file_operations scull_fops = {
	.owner = THIS_MODULE,
	.ioctl = scull_ioctl,
	.open = scull_open,
	.release = scull_release
};

static int scull_open(struct inode *inode, struct file *filp)
{
	return 0;
}

static int scull_release(struct inode *inode, struct file *filp)
{
	return 0;
}


static int scull_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg)
{
	return 0;
}


static int __init scull_init(void)
{
	int result = 0;
	
	scull.major = 0;	
	result = register_chrdev(scull.major, SCULL_DEVICE_NAME, &scull_fops);
	scull.major = result;
	
	
	printk("Hello, world!\n");	
	printk("scull_driver major: %u minor: dev: %u\n", scull.major, scull.dev);
	return 0;
}

static void __exit scull_exit(void)
{
	printk("Goodbye, cruel world!\n");
	printk("Removing device: %u\n", scull.major);
	unregister_chrdev(scull.major, SCULL_DEVICE_NAME);
}

module_init(scull_init);
module_exit(scull_exit);