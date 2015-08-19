#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>  //misc_register

int my_open (struct inode *inode, struct file *filp)
{
	printk("my_open()\n");
	return 0;
}
int my_close(struct inode *inode, struct file *filp)
{
	printk("my_close()\n");
	return 0;
}

long my_ioctl (struct file *filp, unsigned int cmd, unsigned long opt)
{
	_IOC_SIZE(cmd)
	printk("my_ioctl()\n");
	switch( cmd )
	{
		case 1: printk("LED_ON"); break;
		case 2: printk("LED_OFF"); break;
	}
	return 0;
}

static  struct file_operations fops = 
{
	.open           = my_open,
	.release        = my_close,
	.unlocked_ioctl = my_ioctl, 
	.compat_ioctl   = my_ioctl,
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
	misc_deregister( &misc );
}

MODULE_LICENSE("GPL");
module_init( my_init );
module_exit( my_exit );

