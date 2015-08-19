#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>
#include <linux/workqueue.h>

static struct work_struct work;

irqreturn_t my_handler(int irq, void *id)
{
	printk("my_handler()\n");
	schedule_work( &work );
	return IRQ_HANDLED;
}
void my_work_handler(struct work_struct *work)
{
	printk("my_work_handler()\n");
}

int my_init(void)
{
	int ret;
	unsigned long flags=IRQF_SHARED;
	flags |= IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING;
	ret = request_irq(342, my_handler, flags, "MY_INT", my_handler);
	INIT_WORK(&work, my_work_handler);
	return 0;
}

void my_exit(void)
{
	free_irq( 342, my_handler);
}

MODULE_LICENSE("GPL");
module_init( my_init );
module_exit( my_exit );

