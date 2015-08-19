#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>  //misc_register
#include <linux/wait.h>
#include <linux/timer.h>
#include <asm/uaccess.h>
#include <linux/poll.h>

static int temp;
static DECLARE_WAIT_QUEUE_HEAD(my_wait);
static struct timer_list timer;

void my_function(unsigned long data)
{
	printk("my_function(%lu)\n", data );
	temp = 28;
	wake_up_interruptible( &my_wait );
}
int my_open (struct inode *inode, struct file *filp)
{
	init_timer( &timer );
	timer.expires  = jiffies + 3*HZ;
	timer.function = my_function;
	timer.data     = 0;
	add_timer( &timer );
	temp = -999;
	printk("my_open()\n");
	return 0;
}
int my_close(struct inode *inode, struct file *filp)
{
	printk("my_close()\n");
	return 0;
}


unsigned int my_poll(struct file *filp, struct poll_table_struct *table)
{
	unsigned int mask=0;
	printk("my_poll()\n");

	poll_wait(filp, &my_wait, table);
	if( temp != -999 )
		mask = POLLIN;
	return mask;
}

ssize_t my_read (struct file *filp, char __user *buff, size_t size, 
		         loff_t *off)
{
	printk("my_read()\n");
	put_user( temp, (int*)buff );
	return 4;
}

static  struct file_operations fops = 
{
	.open    = my_open,
	.release = my_close,
	.poll    = my_poll, 
	.read    = my_read,
};

static struct miscdevice  misc =
{
	.minor = MISC_DYNAMIC_MINOR, 
	.name  = "mydev", 
	.fops  = &fops, 
};

int my_init(void)
{
	misc_register( &misc );
	return 0;
}

void my_exit(void)
{
	del_timer( &timer );
	misc_deregister( &misc );
}

MODULE_LICENSE("GPL");
module_init( my_init );
module_exit( my_exit );

