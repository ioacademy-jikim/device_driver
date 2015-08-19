#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    mknod("mydev", S_IFCHR | 0666, (200<<8) | 0 );
	return 0;
}
