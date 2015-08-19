#if 1
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>

int main()
{
	int fd;
	char *p;
	fd = open("/dev/mydev", O_RDWR );
	p = mmap(0, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	strcpy( p , "hello world\n");
	printf("%s\n", p );
	munmap(p, 4096);
	close(fd);
	return 0;
}

#endif

