#include <stdio.h>
typedef struct
{
	int queue[64];
	int head;
	int tail;
	int count;
} QUEUE;

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
int main()
{
	QUEUE q;
	init( &q );
	put( &q, 1 );
	put( &q, 2 );
	put( &q, 3 );
	while( !is_empty( &q ) )
		printf("%d\n", get(&q) );
	return 0;
}




