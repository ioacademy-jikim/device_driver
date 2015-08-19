#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/gfp.h>
// /data/aaa
int my_init(void) {
	char *buff;
	struct file *filp;
	int ret;
	filp = filp_open( "/data/bbb", O_WRONLY|O_TRUNC|O_CREAT, 0666 );
	if( filp == 0 )
		return 0;
	buff = (char*)__get_free_pages( GFP_KERNEL, 0 );
	strcpy(buff, "hello world");
	ret = kernel_write( filp, buff, strlen(buff), 0 );
	printk("ret=%d\n", ret );
	free_pages( (unsigned long)buff, 0 );
	filp_close( filp, 0 );
	return 0;
}

void my_exit(void)
{
}

MODULE_LICENSE("GPL");
module_init( my_init );
module_exit( my_exit );

