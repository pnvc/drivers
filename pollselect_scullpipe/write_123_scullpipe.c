#include <unistd.h>
#include <fcntl.h>
int main()
{
	int fd = open("/dev/scullpipe", O_WRONLY);
	char buf[10] = "123";
	write(fd, buf, 3);
	return 0;
}
