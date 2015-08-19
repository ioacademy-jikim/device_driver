#include <linux/module.h>  // my_init
#include <linux/kernel.h>  // printk
#include <linux/sched.h>   // task_struct
#include <linux/list.h>    // kernel list

int my_init(void)
{
	struct task_struct *p;
	struct list_head *temp;

	for( temp = current->tasks.next; 
			temp!= &current->tasks; 
			temp = temp->next )
	{
		p = list_entry( temp, struct task_struct, tasks );
		printk("pid=%d , comm=%s\n", p->pid, p->comm);
	}
	p = list_entry( temp, struct task_struct, tasks );
	printk("pid=%d , comm=%s\n", p->pid, p->comm);

	return 0;
}

void my_exit(void)
{
}

MODULE_LICENSE("GPL");
module_init( my_init );
module_exit( my_exit );

