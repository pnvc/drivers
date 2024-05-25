#include <sys/ioctl.h>
#include "user_headers/scullpipe.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main()
{
	char buf[10];
	int fd = open("/dev/scullpipe", O_RDONLY);

//	write(fd, "123", 3);
	read(fd, buf, 3);
	printf("%s\n", buf);

	printf("%i\n", ioctl(fd, SP_IOC_BUFSIZE_QUERY));
	printf("%s\n", strerror(errno));

	return 0;
}
