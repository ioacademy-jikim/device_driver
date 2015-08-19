#if 1
#include <fcntl.h>
#include <stdio.h>
#include <poll.h>
int main()
{
	char buff[1024];
	int ret;
	int fd;
	struct pollfd fds[2];
	// mkfifo myfifo
	fd = open("myfifo", O_RDWR );
	while(1)
	{
		fds[0].fd = 0;
		fds[0].events = POLLIN;
		fds[1].fd = fd;
		fds[1].events = POLLIN;
		poll( fds, 2, -1);
		if( fds[0].revents & POLLIN )
		{
			ret = read(0, buff, sizeof buff );
			buff[ret-1] = 0;
			printf("키보드 [%s]\n", buff );
		}

		if( fds[1].revents & POLLIN )
		{
			ret = read(fd, buff, sizeof buff );
			buff[ret-1] = 0;
			printf("myfifo [%s]\n", buff );
		}
	}
	close(fd);
	return 0;
}
#endif
#if 0
#include <fcntl.h>
#include <stdio.h>
int main()
{
	char buff[1024];
	int ret;
	int fd;
	// mkfifo myfifo
	fd = open("myfifo", O_RDWR );
	while(1)
	{
		ret = read(0, buff, sizeof buff );
		buff[ret-1] = 0;
		printf("키보드 [%s]\n", buff );

		ret = read(fd, buff, sizeof buff );
		buff[ret-1] = 0;
		printf("myfifo [%s]\n", buff );
	}
	close(fd);
	return 0;
}
#endif


#if 0
#include <fcntl.h>
int main()
{
	char buff[1024];
	int ret;
	ret = read(0, buff, sizeof buff );
	write( 1, buff, ret );
	return 0;
}
#endif
