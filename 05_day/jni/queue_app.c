#if 1
#include <stdio.h>
#include <poll.h>
#include <fcntl.h>

int main()
{
	int i;
	int fd, ret;
	int temp[64];
	fd = open( "/dev/mydev", O_RDONLY );
	while (ret = read( fd, temp, sizeof temp ))
	{
		for( i=0 ; i<(ret/(int)sizeof(int)); i++ )
			printf("temp[%d] = %d\n", i, temp[i] );
	}
	close(fd);
	return 0;
}
#endif

