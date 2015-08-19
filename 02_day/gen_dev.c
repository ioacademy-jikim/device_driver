#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/kdev_t.h>
#include <linux/device.h>

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

static  struct file_operations fops = 
{
	.open    = my_open,
	.release = my_close,
};

static dev_t devt;
static struct class *my_class;
int my_init(void)
{
	devt = MKDEV(200, 0);
	my_class = class_create(THIS_MODULE, "mydev");
	register_chrdev(200, "mydev", &fops );
	device_create(my_class, 0, devt, &fops, "%s", "mydev");
	return 0;
}

void my_exit(void)
{
	device_destroy(my_class, devt);
	unregister_chrdev( 200, "mydev" );
	class_destroy(my_class);
}

MODULE_LICENSE("GPL");
module_init( my_init );
module_exit( my_exit );

