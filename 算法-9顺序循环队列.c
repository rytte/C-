#include <stdio.h>

#define MAX_SIZE 10

// 循环顺序队列节点
struct queue_node 
{
	int data;
};


void queue_enter(struct queue_node* q, int new_data);		// 入队
void queue_show(struct queue_node* q);						// 显示队列中所有的数据
int queue_deq(struct queue_node* q, int* deq_data);			// 出队

int front; // 队头下标
int rear;	// 队尾下标

int main()
{
	struct queue_node q[MAX_SIZE] = { 0 };				// 初始化一个空队列
	front = rear = 0;									// 最初都为0

	int cmd;											// 数据操作（输入非0入队，输入0出队）
	while (1)
	{
		printf("Pls Input: ");
		scanf("%d", &cmd); while (getchar() != '\n');
		if (cmd != 0) // 入队
			queue_enter(q, cmd);
		else if (cmd == 0) // 出队
		{
			queue_deq(q, &cmd);
			printf("get: %d\n", cmd);
		}
		queue_show(q); // 遍历队列
		
	}

	return 0;
}

// 出队
int queue_deq(struct queue_node* q, int* deq_data)
{
	if (rear == front)						// 判断是否空队列
	{
		printf("ERROR: Empty!\n");
		return -1;
	}

	*deq_data = q[front].data;				// 将下标为front的数据取出
	q[front].data = 0;						// 置0，表示数据已经被取出

	front = (front + 1) % MAX_SIZE;			// 队头后移

}

// 显示队列中所有的数据
void queue_show(struct queue_node* q)
{
	int i;
	if (front < rear)
	{
		for (i = front; i < rear; i++)
			printf("%d ", q[i].data);
		printf("\n");
	}
	else if (front > rear)
	{
		for (i = front; i < MAX_SIZE; i++)	// 最大节点之前
			printf("%d ", q[i].data);
		for (i = 0; i < rear; i++)			// 最大节点之后
			printf("%d ", q[i].data);
		printf("\n");
	}
}

// 入队
void queue_enter(struct queue_node* q, int new_data)
{
	if ((rear + 1) % MAX_SIZE == front)		// 判断是否队满
	{
		printf("ERROR: Queue Full!\n");
		return;
	}

	q[rear].data = new_data;				// 将数据写入下标队尾rear位置

	rear = (rear + 1) % MAX_SIZE;			// 更新队尾rear，如果等于MAX_SIZE,置0
}