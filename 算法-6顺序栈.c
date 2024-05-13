#include <stdio.h>

#define SEQ_STACK_SIZE 10

// 顺序栈数据节点
struct seq_stack 
{
	int data;
};

// 栈顶下标：
int g_n;

void stack_push(int new_data, struct seq_stack* s);
int stack_pop(int* pop_data, struct seq_stack* s);
void stack_show(struct seq_stack* s);

int main()
{
	// 1.初始化一个顺序栈
	struct seq_stack ss[SEQ_STACK_SIZE] = { 0 };
	g_n = -1; // 空栈
	// 2.数据操作（输入非0入栈，输入0出栈）
	int cmd;
	int pop_data;
	while (1)
	{
		printf("Pls Input: ");
		scanf("%d", &cmd); while (getchar() != '\n');
		if (cmd == 0)
		{
			if (stack_pop(&pop_data, ss) == 0) // 出栈/弹栈
				printf("%d\n", pop_data);
		}
		else
			stack_push(cmd, ss); // 入栈/压栈
		stack_show(ss);
	}

	return 0;
}

// 显示顺序栈中的每一个数据
void stack_show(struct seq_stack* s)
{
	int i;
	for (i = 0; i <= g_n; i++)
		printf("%d ", s[i].data);
	printf("\n");
}

// 数据删除，出栈（弹栈）
int stack_pop(int* pop_data, struct seq_stack* s)
{
	// 1.判断是否为空栈
	if (g_n == -1)
	{
		printf("ERROR: Empty!\n");
		return -1;
	}
	// 2.将栈顶元素取出
	*pop_data = s[g_n].data;
	// 3.栈顶下标--
	g_n--;
	return 0;
}

// 增加数据（入栈）
void stack_push(int new_data, struct seq_stack* s)
{
	// 1.判断是否满栈
	if (g_n >= SEQ_STACK_SIZE - 1)
	{
		printf("ERROR: Full\n");
		return;
	}
	// 2.将新数据放到栈顶下标+1
	s[g_n + 1].data = new_data;
	// 3.栈顶下标++
	g_n++;
}