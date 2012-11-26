#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/mutex.h>

#include "scull_magic.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Varun Madahar");

#define SCULL_DEVICE_NAME "scull_driver"

#define NUM_OF_DEVICES 1

#ifdef HAVE_UNLOCKED_IOCTL
	static long scull_ioctl(struct file *filp, unsigned int cmd, unsigned long arg);
#else
	static int scull_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg);
#endif

static int scull_open(struct inode *inode, struct file *filp);
static int scull_release(struct inode *inode, struct file *filp);

/* Scull Mutex lock */
static DEFINE_MUTEX(scull_lock);

typedef struct scull_s
{
	int major;
	int data;
} scull_t;
scull_t scull;

struct file_operations scull_fops = {
	.owner = THIS_MODULE,
#ifdef HAVE_UNLOCKED_IOCTL
	.unlocked_ioctl = scull_ioctl,
#else
	.ioctl = scull_ioctl,
#endif
	.open = scull_open,
	.release = scull_release
};

static int scull_open(struct inode *inode, struct file *filp)
{
	printk("scull_open\n");
	
	scull.data = 1;
	filp->private_data = &scull;
	
	return 0;
}

static int scull_release(struct inode *inode, struct file *filp)
{
	printk("scull_close\n");
	return 0;
}


#ifdef HAVE_UNLOCKED_IOCTL
static long scull_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	int result = 0;
	scull_t *scull_data = filp->private_data;
	
	printk("Going in ioct\n");
	
	if (mutex_lock_interruptible(&scull_lock))
        return -ERESTARTSYS;
    
	switch(cmd)
	{
		case SCULL_WRITE_DATA:
		{
			int temp = 0;
			result = __copy_from_user((void*)&temp, (void*)arg, sizeof(int));
			if (result)
			{
				printk("Unable to copy from user\n");
				mutex_unlock(&scull_lock);
				return -1;
			}
			printk("Writing data to: %u\n", temp);
			scull_data->data = temp;
			
		}break;
		case SCULL_READ_DATA:
		{
			result = __copy_to_user((void*)arg, &scull_data->data, sizeof(int));
			if (result)
			{
				printk("Unable to copy to user\n");
				mutex_unlock(&scull_lock);
				return -1;
			}
			printk("Reading data to: %u\n", scull_data->data);
		}break;
		default:
		{
			printk("Error could not find ioctl\n");
		}
	}
	
	mutex_unlock(&scull_lock);
	return 0;
}
#else
static int scull_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg)
{
	int result = 0;
	scull_t *scull_data = filp->private_data;
	
	printk("Going in ioct\n");
	
	if (mutex_lock_interruptible(&scull_lock))
        return -ERESTARTSYS;
    
	switch(cmd)
	{
		case SCULL_WRITE_DATA:
		{
			int temp = 0;
			result = __copy_from_user((void*)&temp, (void*)arg, sizeof(int));
			if (result)
			{
				printk("Unable to copy from user\n");
				mutex_unlock(&scull_lock);
				return -1;
			}
			printk("Writing data to: %u\n", temp);
			scull_data->data = temp;
			
		}break;
		case SCULL_READ_DATA:
		{
			result = __copy_to_user((void*)arg, &scull_data->data, sizeof(int));
			if (result)
			{
				printk("Unable to copy to user\n");
				mutex_unlock(&scull_lock);
				return -1;
			}
			printk("Reading data to: %u\n", scull_data->data);
		}break;
		default:
		{
			printk("Error could not find ioctl\n");
		}
	}
	
	mutex_unlock(&scull_lock);
	return 0;
}
#endif



static int scull_read_proc(char *buf, char **start, off_t offset, int count, int *eof, void *data)
{
	int len=0;
	
	if (mutex_lock_interruptible(&scull_lock))
        return -ERESTARTSYS;

	len += sprintf(buf+len, "Device major: %d data: %u\n", scull.major, scull.data);
	
	mutex_unlock(&scull_lock);
	
	*eof = 1;
	return len;
}

static int __init scull_init(void)
{
	int result = 0;
	
	scull.major = 0;
	scull.data = 22;
	result = register_chrdev(scull.major, SCULL_DEVICE_NAME, &scull_fops);
	scull.major = result;
	
	printk("Creating proc entry for scull_device\n");
	create_proc_read_entry("scull_dev", 0, NULL, scull_read_proc, NULL);
	
	
	printk("Hello, world!\n");	
	printk("scull_driver major: %u\n", scull.major);
	return 0;
}

static void __exit scull_exit(void)
{
	printk("Goodbye, cruel world!\n");
	printk("Removing device: %u\n", scull.major);
	remove_proc_entry("scull_dev", NULL);
	unregister_chrdev(scull.major, SCULL_DEVICE_NAME);
}

module_init(scull_init);
module_exit(scull_exit);