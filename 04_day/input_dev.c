#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>  //misc_register
#include <linux/wait.h>
#include <asm/uaccess.h>
#include <linux/interrupt.h>
#include <linux/input.h>

static struct input_dev *my_input;

irqreturn_t my_handler_up(int irq, void *id)
{
	printk("my_handler_up()\n");
	input_sync(my_input);
	return IRQ_HANDLED;
}
irqreturn_t my_handler_down(int irq, void *id)
{
	static int value=0;
	printk("my_handler_down()\n");
	input_report_key(my_input, KEY_VOLUMEDOWN, value^=1);
	return IRQ_HANDLED;
}

int my_init(void)
{
	int ret;
	unsigned long flags=IRQF_SHARED;
	my_input = input_allocate_device();
	__set_bit( EV_KEY, my_input->evbit);
	__set_bit( KEY_VOLUMEDOWN, my_input->keybit);
	__set_bit( KEY_VOLUMEUP, my_input->keybit);

	ret = input_register_device(my_input);
	flags |= IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING;
	ret = request_irq(342, my_handler_down, flags, "MY_INT_DOWN", my_handler_down);
	ret = request_irq(379, my_handler_up, flags, "MY_INT_UP", my_handler_up);
	return 0;
}

void my_exit(void)
{
	free_irq( 342, my_handler_down);
	free_irq( 379, my_handler_up);
	input_unregister_device(my_input);
}

MODULE_LICENSE("GPL");
module_init( my_init );
module_exit( my_exit );

