#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>  //misc_register
#include <asm/uaccess.h>  //get_user, put_user

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
ssize_t my_write (struct file *filp, const char __user *buff, 
		          size_t size, loff_t *off)
{
	int ret, len;
	char k_buff[5];
	printk("my_write()\n");
	len = (size>sizeof(k_buff)-1)? sizeof(k_buff)-1 : size;
	
	ret = copy_from_user( k_buff, buff, len );
	k_buff[len] = 0;
	printk("%s\n", k_buff);
	return len;
}
/*
ssize_t my_write (struct file *filp, const char __user *buff, 
		          size_t size, loff_t *off)
{
	int i, len;
	char k_buff[5];
	printk("my_write()\n");
	len = sizeof(k_buff)-1;
	
	for(i=0; i<size; i++ )
	{
		if( i >= len ) 
			break;
		get_user( k_buff[i], buff+i);  // k_buff[i] = *(buff+i);
	}
	k_buff[i] = 0;
	printk("%s\n", k_buff);
	return i;
}
*/
/*
ssize_t my_write (struct file *filp, const char __user *buff, 
		          size_t size, loff_t *off)
{
	int k_buff;
	printk("my_write()\n");
	get_user( k_buff, (int*)buff );  // k_buff = *(int*)buff;
	printk("%d\n", k_buff);
	return sizeof(int);
}
*/
ssize_t my_read (struct file *filp, char __user *buff, 
		         size_t size, loff_t * off)
{
	char k_buff[] = "Hello user!!";
	int len = strlen(k_buff);
	int ret;

	len = (size-1>len)? len: size-1;
	printk("my_read()\n");
	ret = copy_to_user( buff, k_buff, len );  // *(buff+i) = k_buff[i];
	return len;
}
/*
ssize_t my_read (struct file *filp, char __user *buff, 
		         size_t size, loff_t * off)
{
	char k_buff[] = "Hello user!!";
	int i;
	printk("my_read()\n");
	for(i=0; k_buff[i]; i++)
	{
		if( i >= size-1 )
			break;
		put_user( k_buff[i], buff+i );  // *(buff+i) = k_buff[i];
	}
	return i;
}
*/
/*
ssize_t my_read (struct file *filp, char __user *buff, 
		         size_t size, loff_t * off)
{
	int temp=28;
	printk("my_read()\n");
	put_user( temp, (int*)buff );  // *(int*)buff = temp;
	return sizeof temp;
}
*/
static  struct file_operations fops = 
{
	.open    = my_open,
	.release = my_close,
	.write   = my_write,
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
	misc_deregister( &misc );
}

MODULE_LICENSE("GPL");
module_init( my_init );
module_exit( my_exit );

