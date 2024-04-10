#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <poll.h>
#include <sys/select.h>

int main()
{
	int fd = open("/dev/scullpipe", O_RDONLY);
	if (fd < 0)
		printf("%s\n", strerror(errno));

	struct pollfd pfd;
	pfd.fd = fd;
	pfd.events |= POLLIN;

	int poll_return = poll(&pfd, 1, -1);
	if (!poll_return)
		printf("%s\n", "timed out");
	if (poll_return < 0)
		printf("%s\n", strerror(errno));
	if (poll_return > 0) {
		printf("%i\n", poll_return);
		printf("%i\n", pfd.revents);
		if (pfd.revents & (POLLIN | POLLRDNORM)) {
			char buf[10];
			read(fd, buf, 10);
			printf("%s\n", buf);
		}
	}

	fd_set readfds;
	FD_SET(fd, &readfds);

	select(fd + 1, &readfds, NULL, NULL, NULL);

	if (FD_ISSET(fd, &readfds)) {
		char buf[10];
		read(fd, buf, 10);
		printf("%s\n", buf);
	}

	return 0;
}
