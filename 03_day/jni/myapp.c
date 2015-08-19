#include <fcntl.h>
int main()
{
	int fd;
	fd = open( "/sys/devices/virtual/misc/mydev/uevent", O_WRONLY );
	write( fd, "add\n", 4 );
	close(fd);
	return 0;
}

