#include <linux/module.h>  // my_init
#include <linux/kernel.h>  // printk
#include <linux/sched.h>   // task_struct

int my_init(void)
{
	struct task_struct *p;
	for_each_process(p)
		printk("pid=%d , comm=%s\n", p->pid, p->comm);

	return 0;
}

void my_exit(void)
{
}

MODULE_LICENSE("GPL");
module_init( my_init );
module_exit( my_exit );

