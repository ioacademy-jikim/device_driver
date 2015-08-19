#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>  //misc_register
#include <linux/wait.h>
#include <asm/uaccess.h>
#include <linux/interrupt.h>

static int temp;
static DECLARE_WAIT_QUEUE_HEAD(my_wait);

int my_open (struct inode *inode, struct file *filp)
{
	temp = -999;
	printk("my_open()\n");
	return 0;
}
int my_close(struct inode *inode, struct file *filp)
{
	printk("my_close()\n");
	return 0;
}

irqreturn_t my_handler(int irq, void *id)
{
	printk("my_handler()\n");
	temp=23;
	wake_up_interruptible(&my_wait);
	return IRQ_HANDLED;
}

ssize_t my_read (struct file *filp, char __user *buff, size_t size, 
		         loff_t *off)
{
	printk("my_read()\n");
	if( temp == -999 )
		interruptible_sleep_on(&my_wait);
	put_user( temp, (int*)buff );
	return 4;
}

static  struct file_operations fops = 
{
	.open    = my_open,
	.release = my_close,
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
	int ret;
	unsigned long flags=IRQF_SHARED;
	misc_register( &misc );
	flags |= IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING;
	ret = request_irq(342, my_handler, flags, "MY_INT", my_handler);
	return 0;
}

void my_exit(void)
{
	free_irq( 342, my_handler);
	misc_deregister( &misc );
}

MODULE_LICENSE("GPL");
module_init( my_init );
module_exit( my_exit );

