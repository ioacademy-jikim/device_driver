#include <fcntl.h>
int main()
{
	int fd;
	fd = open( "/dev/mydev", O_RDONLY );
	close(fd);
	return 0;
}

