#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");

static int __init scull_init(void)
{
	printk("Hello, world!\n");
	return 0;
}

static void __exit scull_exit(void)
{
	printk("Goodbye, cruel world!\n");
}

module_init(scull_init);
module_exit(scull_exit);