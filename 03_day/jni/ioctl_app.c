#if 1
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <errno.h>

#define  LED_RATIO   _IOW( 'm', 1 , int)

int main()
{
	int fd, ret;
	int ratio;
	char buff[10];
	printf("밝기 입력( 0-255 ) : ");
	scanf("%d", &ratio );
	fd = open( "/dev/mydev", O_RDONLY );
	ret = ioctl(fd, LED_RATIO, &ratio);
	if( ret < 0 )
	{
		printf("ret=%d, errno=%d\n", ret, errno );
		return 0;
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

