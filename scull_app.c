#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>		/* open */
#include <unistd.h>		/* exit */
#include <sys/ioctl.h>		/* ioctl */

int main()
{
	int file_desc = -1;
	
	file_desc = open("/dev/scull_driver", O_RDWR);
	if (file_desc < 0)
	{
		printf("Error opening scull driver\n");
		return -1;
	}
	
	int temp = 7;
	
	ioctl(file_desc, 1, &temp);
	
	close(file_desc);
	
	return 0;
}
