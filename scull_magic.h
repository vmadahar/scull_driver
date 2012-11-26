#ifndef __SCULL_MAGIC_H_
#define __SCULL_MAGIC_H_

#ifdef __KERNEL__
#include <linux/ioctl.h>
#else
#include <sys/ioctl.h>
#endif

#define SCULL_DEV_BASE (0)

#define SCULL_ID ('A')

#define SCULL_WRITE_DATA _IOW(SCULL_ID, (SCULL_DEV_BASE + 0), int)
#define SCULL_READ_DATA _IOR(SCULL_ID, (SCULL_DEV_BASE +1), int)

#endif
