#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <fcntl.h>

static int a = 0;

void handler(int sn, siginfo_t *si, void *uc)
{
	a = 12;
}

void handler2(int sn)
{
	a = 999;
}

int main()
{
	struct sigaction sa = {
		.sa_flags = SA_SIGINFO,
		.sa_sigaction = &handler,
	};

	sigaction(SIGIO, &sa, NULL);
	//signal(SIGIO, handler2);

	int fd = open("/dev/scullpipe", O_RDONLY);
	int oflags;

	fcntl(fd, F_SETOWN, getpid());
	oflags = fcntl(fd, F_GETFL);
	fcntl(fd, F_SETFL, oflags | FASYNC);

	printf("%i\n", a);

	char buf[100] = {0};

	for (;!a;) {
		sleep(1);
	}

	if (a == 12)
		read(fd, buf, 100);

	write(1, buf, 100);

	close(fd);

	printf("%i\n", a);

	return 0;
}
