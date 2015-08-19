#include <fcntl.h>
#include <stdio.h>
#include <string.h>
int main()
{
	int fd, ret;
	char buff[10];
	fd = open( "/dev/mydev", O_RDONLY );
	ret = read( fd, buff, sizeof buff );
	buff[ret] = 0;
	printf( "buff[%s], ret=%d\n", buff, ret );
	close(fd);
	return 0;
}
/*
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
int main()
{
	int fd, ret;
	int temp;
	fd = open( "/dev/mydev", O_RDONLY );
	ret = read( fd, &temp, sizeof temp );
	printf( "temp=%d, ret=%d\n", temp, ret );
	close(fd);
	return 0;
}
*/

/*
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
int main()
{
	int fd, ret;
	char buff[] = "LED_ON";
	fd = open( "/dev/mydev", O_WRONLY );
	ret = write( fd, buff, strlen(buff) );
	printf( "ret=%d\n", ret );
	close(fd);
	return 0;
}
*/
/*
#include <fcntl.h>
int main()
{
	int fd;
	int flag=128;
	fd = open( "/dev/mydev", O_WRONLY );
	write( fd, &flag, sizeof flag );
	close(fd);
	return 0;
}
*/
