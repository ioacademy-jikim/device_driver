#if 1
#include <stdio.h>
struct aaa
{
	int count;
	int flag;
	int data[];
};

int main()
{
	struct aaa *p;
	p = malloc( sizeof(struct aaa) + sizeof(int)*100 );
	p->count = 0;
	p->data[0] = 10;
	return 0;
}
#endif

#if 0
#include <stdio.h>
struct aaa
{
	int a;
	int b[];
};

int main()
{
	struct aaa a;
	printf("sizeof(a)=%lu\n", sizeof a );
	return 0;
}
#endif
