#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>		/* open */
#include <unistd.h>		/* exit */
#include <sys/ioctl.h>		/* ioctl */

#include "scull_magic.h"

int main()
{
	int file_desc = -1;
	int err = 0;
	
	file_desc = open("/dev/scull_driver", O_RDWR);
	if (file_desc < 0)
	{
		printf("Error opening scull driver\n");
		return -1;
	}
	
	int temp = 7;
	
	err = ioctl(file_desc, SCULL_WRITE_DATA, &temp);
	if (err)
		printf("Error trying to write data\n");
	
	err = ioctl(file_desc, SCULL_READ_DATA, &temp);
	if (err)
		printf("Error trying to read data\n");
	
	printf("Read data from the scull driver: %u\n", temp);	
	
	
	close(file_desc);
	
	return 0;
}
