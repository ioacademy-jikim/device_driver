#include <stdio.h>
struct list_head {
	struct list_head *next, *prev;
};

struct miscdevice  {
	int minor;
	const char *name;
	struct list_head list;
};


static inline void __list_add(struct list_head *new,
			      struct list_head *prev,
			      struct list_head *next)
{
	next->prev = new;
	new->next = next;
	new->prev = prev;
	prev->next = new;
}

static inline void list_add(struct list_head *new, struct list_head *head)
{
	__list_add(new, head, head->next);
}

#define LIST_HEAD_INIT(name) { &(name), &(name) }

#define LIST_HEAD(name) \
	struct list_head name = LIST_HEAD_INIT(name)

#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

#define container_of(ptr, type, member) ({			\
	const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
	(type *)( (char *)__mptr - offsetof(type,member) );})

#define list_entry(ptr, type, member) \
	container_of(ptr, type, member)

#define list_for_each_entry(pos, head, member)				\
	for (pos = list_entry((head)->next, typeof(*pos), member);	\
	     &pos->member != (head); 	\
	     pos = list_entry(pos->member.next, typeof(*pos), member))

static LIST_HEAD(misc_list);
static struct miscdevice misc =  {
	.minor = 24,
	.name  = "mydev",
};

int main()
{
	struct miscdevice *c;
	list_add(&misc.list, &misc_list);

    list_for_each_entry(c, &misc_list, list) {
		printf("minor=%d, name=%s\n", c->minor, c->name );
	}
	return 0;
}





