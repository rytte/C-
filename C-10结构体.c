/********************/结构体/************************************************************/
结构体(struct)是由一系列具有相同类型或不同类型的数据构成的数据集合，也叫结构。

关键字 struct

结构体类型声明时可以同时定义变量，声明结束需要带分号";"。

//字节对齐
结构体的大小不是结构体元素单纯相加就行的，因为我们现在主流的计算机使用的都是32Bit字长的CPU，
对这类型的CPU取4个字节的数要比取一个字节要高效，也更方便。
所以在结构体中每个成员的首地址都是4的整数倍的话，取数据元素时就会相对更高效，这就是内存对齐的由来。
每个特定平台上的编译器都有自己的默认“对齐系数”(也叫对齐模数)。
程序员可以通过预编译命令#pragmapack(n)，n = 1, 2, 4, 8, 16来改变这一系数，其中的n就是你要指定的“对齐系数”。

规则
1、数据成员对齐规则：结构(struct)(或联合(union))的数据成员，第一个数据成员放在offset为0的地方，
以后每个数据成员的对齐按照#pragmapack指定的数值和这个数据成员自身长度中，比较小的那个进行。
2、结构(或联合)的整体对齐规则：在数据成员完成各自对齐之后，结构(或联合)本身也要进行对齐，
对齐将按照#pragmapack指定的数值和结构(或联合)最大数据成员长度中，比较小的那个进行。
3、结合1、2可推断：当#pragmapack的n值等于或超过所有数据成员长度的时候，这个n值的大小将不产生任何效果。



/********************/结构体赋值/************************************************************/
#include <stdio.h>
#include <string.h>
// 构造一个结构体模板（声明一种结构体类型）
struct student {
	char name[20]; 	//成员1：char [20]类型的数组
	int age;		//成员2：int 整型
	char sex;		//成员3：char 字符型
	float score;	//成员4：float 浮点型
};

int main()
{
	struct student stu_thr = {
		.name = "Tom",
		.age = 20,
		.sex = 'm',
		.score = 60
	};
	// 结构体变量赋值
	struct student stu_fou = stu_thr;
	printf("%s\n", stu_fou.name);
	printf("%d\n", stu_fou.age);
	printf("%c\n", stu_fou.sex);
	printf("%f\n", stu_fou.score);

	return 0;
}



/********************/结构体传参/************************************************************/
#include <stdio.h>
#include <string.h>

// 构造一个结构体模板（声明一种结构体类型）
struct stu {
	int id; 		// 成员1：学号
	char name[32];	// 成员2：姓名
	char sex;		// 成员3：性别
	float score;	// 成员4：分数
};
// 子函数中，形参里包括结构体类型的，需要在结构体之后，main函数之前声明
// void show_info(struct stu show); // 函数声明 值传递
void show_info(struct stu* show); // 函数声明 地址传递

int main()
{
	// 现在数组元素的类型为结构体类型
	// struct stu my_class[50] = {
	// 	{1, "jack", 'm', 90.5}, // 数组的第一个元素
	// 	{2, "Rose", 'w', 85.5}, // 数组的第二个元素
	// 	{3,	"Tom",	'm', 81}
	// };

	/****************指定成员初始化**************/
	struct stu my_class[50] = {
		{.id = 1,
			.name = "Jack",
			.sex = 'm',
			.score = 90.5
		},
		{.id = 2,
			.name = "Rose",
			.sex = 'w',
			.score = 85.5
		},
		{.id = 3,
			.name = "Tom",
			.sex = 'm',
			.score = 81
		}
	};
	show_info(my_class);
	// show_info(my_class+1);
	// show_info(my_class+2);
	return 0;
}

// 结构体类型：关键字+标签
// void show_info(struct stu show) // 值传递
// {
// 	printf("ID\t Name\t Sex\t Score\n");//打印表头
// 	printf("%d\t %s\t %c\t %.1f\n", 
// 	show.id, show.name, show.sex, show.score);
// }

// 地址传递
void show_info(struct stu* show)
{
	printf("ID\t Name\t Sex\t Score\n");//打印表头
	for (int i = 0; i < 3; i++)
	{
		// printf("%d\t %s\t %c\t %.1f\n", 
		// show->id, show->name, show->sex, show->score);
		// show++;
		printf("%d\t %s\t %c\t %.1f\n",
			(show + i)->id,
			(show + i)->name,
			(show + i)->sex,
			(show + i)->score);

	}
}