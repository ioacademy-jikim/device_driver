#include <linux/module.h>
#include <linux/kernel.h>

int my_init(void)
{
	printk("init_module()\n");
	return 0;
}

void my_exit(void)
{
	printk("cleanup_module()\n");
}

MODULE_LICENSE("GPL");
module_init( my_init );
module_exit( my_exit );

