#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>  //misc_register
#include <asm/ioctl.h>
#include <asm/uaccess.h>

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
//#define BINDER_WRITE_READ		_IOWR('b', 1, struct binder_write_read)
#define  LED_RATIO   _IOW( 'm', 1, int )

static int ratio;

long my_ioctl(struct file *filp, unsigned int cmd, unsigned long opt)
{
	unsigned int size;
	int ret;
	printk("my_ioctl()\n");

	size = _IOC_SIZE(cmd);

	switch( cmd )
	{
		case LED_RATIO:  
			if( size != sizeof(int))
				return -EINVAL;

			ret = copy_from_user( &ratio, (void*)opt, size); 
		    printk("LED_RATIO, ratio=%d\n", ratio );
			break;
	}
			
	return 0;
}
/*
//#define BINDER_WRITE_READ		_IOWR('b', 1, struct binder_write_read)
#define  LED_RATIO   _IO( 'm', 1 )
static int ratio;

long my_ioctl(struct file *filp, unsigned int cmd, unsigned long opt)
{
	printk("my_ioctl()\n");

	if( _IOC_TYPE(cmd) != 'm' )
		return -EINVAL;

	if( _IOC_NR(cmd) != 1 )
		return -EINVAL;

	switch( cmd )
	{
		case LED_RATIO:  ratio = 128; 
						 printk("LED_RATIO, ratio=%d\n", ratio );
						 break;
	}
			
	return 0;
}
*/

static  struct file_operations fops = 
{
	.open            = my_open,
	.release         = my_close,
	.unlocked_ioctl  = my_ioctl,
	.compat_ioctl    = my_ioctl,
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

