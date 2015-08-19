#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>  //misc_register
#include <linux/mm_types.h>
#include <linux/gfp.h>
#include <linux/mm.h>

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

int my_mmap(struct file *filp, struct vm_area_struct *vma)
{
	unsigned long pfn;
	unsigned long page;
	printk("my_mmap()\n");
	page = __get_free_pages( GFP_KERNEL, 0 );
	pfn = __pa( page );
    remap_pfn_range(vma, vma->vm_start, 
			        pfn>>12, 1<<12, vma->vm_page_prot);
	return 0;
}

static  struct file_operations fops = 
{
	.open    = my_open,
	.release = my_close,
	.mmap    = my_mmap,
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

