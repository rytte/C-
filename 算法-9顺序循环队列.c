#include <stdio.h>

#define SEQ_QUEUE_SIZE 10

// 循环顺序队列节点
struct queue_node {
	int data;
};

// 入队
void queue_enter(struct queue_node* q, int new_data);
// 显示队列中所有的数据
void queue_show(struct queue_node* q);
// 出队
int queue_deq(struct queue_node* q, int* deq_data);

int front; // 队头下标
int rear; // 队尾下标

int main()
{
	// 1.初始化一个空队列
	struct queue_node q[SEQ_QUEUE_SIZE] = { 0 };
	front = rear = 0; // 最初都为0
	// 2.数据操作（输入非0入队，输入0出队）
	int cmd;
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
	// 0.判断是否为空队列
	if (rear == front)
	{
		printf("ERROR: Empty!\n");
		return -1;
	}
	// 1.直接将下标为front的数据取出
	*deq_data = q[front].data;
	q[front].data = 0; //置0，表示数据已经被取出
	// 2.队头后移
	front = (front + 1) % SEQ_QUEUE_SIZE;

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
		for (i = front; i < SEQ_QUEUE_SIZE; i++) // 最大节点之前
			printf("%d ", q[i].data);
		for (i = 0; i < rear; i++) // 最大节点之后
			printf("%d ", q[i].data);
		printf("\n");
	}
}

// 入队
void queue_enter(struct queue_node* q, int new_data)
{
	// 0.判断是否为满队列
	/*int var = rear+1;
	if(var == SEQ_QUEUE_SIZE)
		var = 0;
	if(var == front)
	{
		printf("ERROR: Queue Full!\n");
		return ;
	}*/
	if ((rear + 1) % SEQ_QUEUE_SIZE == front)
	{
		printf("ERROR: Queue Full!\n");
		return;
	}
	// 1.直接将数据写入下标队尾rear位置
	q[rear].data = new_data;

	// 2.队尾后移，rear++,如果等于SEQ_QUEUE_SIZE,置0
	rear = (rear + 1) % SEQ_QUEUE_SIZE;
}