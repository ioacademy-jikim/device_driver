#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>  //misc_register
#include <linux/wait.h>
#include <asm/uaccess.h>
#include <linux/interrupt.h>
#include <linux/input.h>

typedef struct
{
	int queue[64];
	int head;
	int tail;
	int count;
} QUEUE;
static QUEUE queue;
static DECLARE_WAIT_QUEUE_HEAD(my_wait);


void init( QUEUE *q )
{
	q->head  = 0;
	q->tail  = 0;
	q->count = 0;
}
void put( QUEUE *q, int data )
{
	q->queue[q->head] = data;
	q->head = (q->head+1)%64;
	q->count++;
}
int get( QUEUE *q )
{
	int temp;
	temp =  q->queue[q->tail];
	q->tail = (q->tail+1)%64;
	q->count--;
	return temp;
}
int is_empty( QUEUE *q )
{
	return q->count == 0 ;
}

int my_open (struct inode *inode, struct file *filp)
{
	init(&queue);
	printk("my_open()\n");
	return 0;
}
int my_close(struct inode *inode, struct file *filp)
{
	printk("my_close()\n");
	return 0;
}

irqreturn_t my_handler_up(int irq, void *id)
{
	printk("my_handler_up()\n");
	wake_up_interruptible(&my_wait);
	return IRQ_HANDLED;
}
irqreturn_t my_handler_down(int irq, void *id)
{
	printk("my_handler_down()\n");
	put( &queue, KEY_VOLUMEDOWN );
	return IRQ_HANDLED;
}

ssize_t my_read (struct file *filp, char __user *buff, size_t size, 
		         loff_t *off)
{
	int i;
	int *p = (int*)buff;
	printk("my_read()\n");
	if( is_empty(&queue) )
		interruptible_sleep_on(&my_wait);

	for(i=0;  !is_empty(&queue); i++ )
		put_user( get(&queue) , p+i);
	return 4*i;
}

static  struct file_operations fops = 
{
	.open    = my_open,
	.release = my_close,
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
	int ret;
	unsigned long flags=IRQF_SHARED;
	misc_register( &misc );
	flags |= IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING;
	ret = request_irq(342, my_handler_down, flags, "MY_INT_DOWN", my_handler_down);
	ret = request_irq(379, my_handler_up, flags, "MY_INT_UP", my_handler_up);
	return 0;
}

void my_exit(void)
{
	free_irq( 342, my_handler_down);
	free_irq( 379, my_handler_up);
	misc_deregister( &misc );
}

MODULE_LICENSE("GPL");
module_init( my_init );
module_exit( my_exit );

