#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>

irqreturn_t my_handler(int irq, void *id)
{
	printk("my_handler()\n");
	return IRQ_HANDLED;
}

int my_init(void)
{
	int ret;
	unsigned long flags=IRQF_SHARED;
	flags |= IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING;
	ret = request_irq(342, my_handler, flags, "MY_INT", my_handler);
	return 0;
}

void my_exit(void)
{
	free_irq( 342, my_handler);
}

MODULE_LICENSE("GPL");
module_init( my_init );
module_exit( my_exit );

