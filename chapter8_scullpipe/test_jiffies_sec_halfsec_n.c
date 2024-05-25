#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	int fd = open("/dev/scullpipe", O_WRONLY);
	char buf[] = "1";
	for (;;) {
		write(fd, buf, sizeof buf - 1);
		sleep(0.1);
	}
}
