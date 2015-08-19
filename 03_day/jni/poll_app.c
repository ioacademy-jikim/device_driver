#if 1
#include <stdio.h>
#include <poll.h>
#include <fcntl.h>

int main()
{
	int fd, ret;
	int temp;
	char buff[1024];
	struct pollfd fds[2];
	fd = open( "/dev/mydev", O_RDONLY );
	fds[0].fd = 0 ;
	fds[0].events = POLLIN;
	fds[1].fd = fd ;
	fds[1].events = POLLIN;

	poll( fds, 2, -1 );

	if( fds[0].revents & POLLIN )
	{
		read( 0, buff, sizeof buff );
		buff[ret-1] = 0;
		printf("buff=%s\n", buff );
	}
	if( fds[1].revents & POLLIN )
	{
		read( fd, &temp, sizeof temp );
		printf("temp=%d\n", temp );
	}
	close(fd);
	return 0;
}
#endif
#if 0
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <errno.h>

#define  LED_RATIO   _IO( 'm', 1 )

int main()
{
	int fd, ret;
	char buff[10];
	fd = open( "/dev/mydev", O_RDONLY );
	ret = ioctl(fd, LED_RATIO);
	if( ret < 0 )
	{
		printf("ret=%d, errno=%d\n", ret, errno );
		return 0;
	}
	close(fd);
	return 0;
}
#endif

