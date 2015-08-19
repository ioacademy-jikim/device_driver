#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gfp.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>

struct my_struct
{
	char name[20];
	int  id;
};

int my_init(void)
{
	char *p;
	struct my_struct *task;
	struct kmem_cache *my_struct_cachep;
	p = (char*)__get_free_pages( GFP_KERNEL, 0 );
	p[4095] = 'x';
	printk("%c\n", p[4095]);
	free_pages((unsigned long)p, 0);

	p = (char*)kmalloc( 64, GFP_KERNEL);
	p[63] = 'x';
	printk("%c\n", p[63]);
	kfree(p);

#define L1_CACHE_SHIFT		6
#define L1_CACHE_BYTES		(1 << L1_CACHE_SHIFT)
#define ARCH_MIN_TASKALIGN	L1_CACHE_BYTES

	my_struct_cachep =
		kmem_cache_create("my_struct", sizeof(struct my_struct),
			ARCH_MIN_TASKALIGN, SLAB_PANIC | SLAB_NOTRACK, NULL);
	task = kmem_cache_alloc( my_struct_cachep, GFP_KERNEL);
	strcpy( task->name, "kji");
	task->id = 1234;
	printk("%s, %d\n", task->name, task->id);
	kmem_cache_free( my_struct_cachep, task);
	kmem_cache_destroy( my_struct_cachep );

	p = vmalloc( 8192 * 1024 );
	p[8192 * 1024-1] = 'x';
	printk("%c\n", p[8192 * 1024-1] );
	vfree( p );
	return 0;
}

void my_exit(void)
{
}

MODULE_LICENSE("GPL");
module_init( my_init );
module_exit( my_exit );

