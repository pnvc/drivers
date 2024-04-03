#include <stdio.h>
#include "user/scullpipe.h"
#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <string.h>

int main()
{
	char buf[12] = "privet :)";
	int fd = open("/dev/scullpipe", O_RDONLY);
	printf("%d\n", ioctl(fd, SP_IOC_BUFSIZE_QUERY));
	ioctl(fd, SP_IOC_BUFSIZE_TELL, 15);
	printf("%d\n", ioctl(fd, SP_IOC_BUFSIZE_QUERY));
	printf("%s\n", strerror(errno));

	ioctl(fd, SP_IOC_TEST, buf);
	return 0;
}
