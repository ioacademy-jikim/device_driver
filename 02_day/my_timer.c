#if 1
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/timer.h>

static struct timer_list timer;
void my_function(unsigned long data)
{
	printk("my_function(%lu)\n", data );
	timer.data     = data+1;
	mod_timer( &timer, jiffies + HZ);
}
int my_init(void)
{ 
	printk("init_module()\n");
	init_timer( &timer );
	timer.expires  = jiffies + HZ;
	timer.function = my_function;
	timer.data     = 0;
	add_timer( &timer );
	return 0;
}

void my_exit(void)
{
	del_timer( &timer );
	printk("cleanup_module()\n");
}

MODULE_LICENSE("GPL");
module_init( my_init );
module_exit( my_exit );
#endif
#if 0
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/timer.h>

static struct timer_list timer;
void my_function(unsigned long data)
{
	printk("my_function(%lu)\n", data );
}
int my_init(void)
{
	printk("init_module()\n");
	init_timer( &timer );
	timer.expires  = jiffies + 3*HZ;
	timer.function = my_function;
	timer.data     = 0;
	add_timer( &timer );
	return 0;
}

void my_exit(void)
{
	del_timer( &timer );
	printk("cleanup_module()\n");
}

MODULE_LICENSE("GPL");
module_init( my_init );
module_exit( my_exit );
#endif

