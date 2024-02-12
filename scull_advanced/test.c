#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
int main()
{
	int fd  = open("/dev/scull0", O_RDONLY);
	char buf[10];
	if (read(fd, buf, 10) == ERESTART)

		write(1, "a\n", 2);
	return 0;
}
