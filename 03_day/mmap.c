#if 1
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
int main()
{
	int fd;
	char *p;
	printf("main=%p\n", main);
	fd = open("aaa", O_RDWR | O_TRUNC | O_CREAT , 0666 );
	ftruncate(fd, 1024);
	p = mmap(0, 1024, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	strcpy( p , "hello world\n");
	//printf("%s\n", p );
	munmap(p, 1024);
	close(fd);
	return 0;
}
#endif

#if 0
#include <fcntl.h>
int main()
{
	//mmap();

	int fd;
	fd = open("aaa", O_WRONLY | O_TRUNC | O_CREAT , 0666 );
	write( fd, "hello world", 11 );
	close(fd);
	return 0;
}
#endif
