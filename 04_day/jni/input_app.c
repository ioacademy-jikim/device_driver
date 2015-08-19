#if 1
#include <stdio.h>
#include <poll.h>
#include <fcntl.h>
#include <linux/input.h>

int main()
{
	int i;
	int fd, ret;
	struct input_event events[64];
	fd = open( "/dev/input/event4", O_RDONLY );
	while (ret = read( fd, events, sizeof events ))
	{
		for( i=0 ; i<(ret/(int)sizeof(struct input_event)); i++ )
			printf("type=%d, code=%d, value=%d\n", 
					events[i].type, events[i].code, events[i].value);
	}
	close(fd);
	return 0;
}
#endif

