/********************/可变参数宏库/************************************************************/
#include <stdarg.h>

//常用变量
typedef char* va_list;          //va_list：可变参数列表
va_list args;                   //即char* args。 args是用于指向可变参数首地址的指针。

#define va_start(args, last)   (args = (va_list)&last+ sizeof(last))  //初始化args，将其指向可变参数地址列表的首地址（，last是最后一个固定参数）

#define va_arg(args, type)   ((type *) (args += sizeof(type)))[-1]    //返回可变参数的当前参数，并将args指针指向下一参数（type表示当前参数的类型）

#define va_end(args)   ((void)args = (va_list)0)                    //清空va_list可变参数列表

#define va_copy(destination, source)  ((destination) = (source))    //拷贝va_list的内容从src到dst

注：以上sizeof()只是为了说明工作原理，实际实现中，增加的字节数需保证为为int的整数倍
#define _INTSIZEOF(n) ((sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1))    //这个宏确保了无论n的大小如何，返回的结果都是int类型大小的整数倍。

* C语言中函数参数从右往左依次入栈。存储空间为连续存储，且参数按照固定字节对齐（64位平台为8字节）。在 va_arg 使 args 指针指向下一参数时有所体现;



//实例1：计算总和
#include <stdio.h>  
#include <stdarg.h>  

int sum(int num, ...)           // 变参函数定义，第一个参数是后续参数的数量 
{
    va_list args;               // 创建一个va_list类型的变量来存储参数信息  
    va_start(args, num);        // 初始化args变量，num是最后一个固定参数  

    int sum = 0;
    for (int i = 0; i < num; i++)
    {
        sum += va_arg(args, int); // 获取下一个参数（int类型）并加到sum上  
    }
 
    va_end(args);

    return sum;
}

int main()
{
    printf("Sum: %d\n", sum(5, 10, 20, 30, 40, 50)); // 传入5个整数  

    return 0;
}



//实例2：打印多个字符串
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

void var_test(const char* format, ...)              //该实例中，固定参数format没什么用，它不表示可变参数个数
{
    va_list list;
    va_start(list, format);

    char* ch;
    while (1)
    {
        ch = va_arg(list, char*);               //获取当前参数，并指向下一参数

        if (strcmp(ch, "") == 0)
        {
            printf("\n");
            break;
        }
        printf("%s ", ch);
    }
    va_end(list);                                   
}

int main()
{
    var_test("test", "this", "is", "a", "test", "");    //this is a test
    return 0;
}



//实例3：定制错误打印函数error
#include  <stdio.h>
#include  <stdarg.h>

void error(char* format, ...)
{
    va_list ap;
    va_start(ap, format);
    fprintf(stderr, "Error: ");
    vfprintf(stderr, format, ap);
    va_end(ap);
    fprintf(stderr, "\n");
    return;
}

int main()
{
    error("Failed to open file %s.", "example.txt");      //Error : Failed to open file example.txt.
    return 0;
}



/********************/printf()/************************************************************/
printf()函数返回输出字符个数（\n和空格也算）
本例为32位平台，所以参数出入栈地址均为4字节对齐。

#ifndef _VALIST
#define _VALIST
typedef char* va_list;
#endif                /* _VALIST */
typedef int acpi_native_int;
#define  _AUPBND                (sizeof (acpi_native_int) - 1)                               // 入栈4字节对齐
#define  _ADNBND                (sizeof (acpi_native_int) - 1)                              // 出栈4字节对齐
#define _bnd(X, bnd)            (((sizeof (X)) + (bnd)) & (~(bnd)))                      // 4字节对齐
#define va_arg(ap, T)           (*(T *)(((ap) += (_bnd (T, _AUPBND))) - (_bnd (T,_ADNBND)))) // 按照4字节对齐取下一个可变参数,并且更新参数指针
#define va_end(ap)              (void) 0                                                                // 与va_start成对,避免有些编译器告警
#define va_start(ap, A)         (void) ((ap) = (((char *) &(A)) + (_bnd (A,_AUPBND))))       // 第一个可变形参指针
#endif                /* va_arg */

static char sprint_buf[2408];

int printf(const char* fmt, ...)
{
    va_list args;
    int n;

    va_start(args, fmt);
    n = vsprintf(sprint_buf, fmt, args);            // 根据字符串fmt，将对应形参转换为字符串，并组合成新的字符串存储在sprint_buf[]缓存中，返回字符个数。
    va_end(args);                                   // C标准要求在同一个函数中va_start 和va_end 要配对的出现。
        
    //if (console_ops.write)                        // 调用相关驱动接口,将sprintf_buf中的内容输出n个字节到设备，
    //    console_ops.write(sprint_buf, n);         // 此处可以是串口、控制台、Telnet等,在嵌入式开发中可以灵活挂接
    return n;
}


常见组合及输出结果

int main(void)
{
    int a = 10, b = 3;
    printf("%*.*d\n", a, b, -100);         //              -100    //输出数字，右对齐,宽度从变量获取
    printf("%10.3d\n", -100);              //               -100    //输出数字，右对齐
    printf("%-10.3d\n", -100);             // -100                  //输出数字，左对齐
    printf("%+10.3d\n", 100);              //                +100  //输出数字，正数带正号
    printf("%0.13d\n", 100);               // 0000000000100//输出文本格式,如员工号
    printf("%#.8x\n", 0x30ff);             // 0x000030ff        //输出8位16进制地址，小写字母
    printf("%#.8X\n", 0x30ff);             // 0X000030FF      //输出8位16进制地址，大写字母
    printf("%.3f\n", 3.14159267892);       // 3.142                  //保留浮点小数点后有效位数
    printf("%llu\n", 0xffffffffffffffff);  // 18446744073709551615//输出64位长整型
}



/********************/scanf()/************************************************************/
scanf()函数返回成功赋值变量的个数

__scanf(const char* format, ...)
{
        va_list arg;
        int done;

        va_start(arg, format);
        done = __vfscanf_internal(stdin, format, arg, 0);  //实际是对__vfscanf_internal的封装，arg指向可变参数
        va_end(arg);

        return done;
}
ldbl_strong_alias(__scanf, scanf)


vscanf - internal.c
函数原型
int __vfscanf_internal(FILE * s, const char* format, va_list argptr, unsigned int mode_flags)
原理：
在vfscanf中有两个流：一个是指导读入格式的字符串流format，一个是被读入的流s
vfscanf先逐字符解析format，解析出一个要读入的格式后，就会调用inchar()从流s中逐字符读入
例如format = "%d%"，输入"13\n"
vfcanf解析出 % d后指导要从流s中读入一个十进制整数，于是调用inchar()得到字符'1'，继续调用inchar()得到'2'，
再次调用inchar()得到字符'\n'，vfscanf就知道一个整数已经结束了，就把'\n'放回流s中，然后把读入的"12"转化为int 12
其余的同理



//scanf()注意事项
scanf("%d", &id); while (getchar() != '\n');                    //此句scanf()结束后的换行符'\n'，会被下句scanf()接收，因此需要while ()消除此'\n'
scanf("%s", &name); while (getchar() != '\n');



/********************/格式控制符/************************************************************/
格式字符		意义
% a, % A	十六进制浮点数（C99 新增）。//实例 printf("pi=%a\n", 3.14); 输出 pi = 0x1.91eb86p+1。
% d			十进制有符号整数（正数不输出正号）
% o			八进制无符号整数（不输出前缀0）
% x, % X	十六进制无符号整数（不输出前缀0x）
% u			十进制无符号整数
% f			小数形式单、双精度实数
% e, % E	指数形式单、双精度实数
% g, % G	以% f或% e中较短的输出宽度输出单、双精度实数
% c			单个字符
% s			字符串
% p			指针地址
% lu		32位无符号整数
% llu		64位无符号整数
% %         不转换参数，输出字符%
% #         提示进制信息，如果是8进制在前面加0，如果是十六进制会加上0x。




/********************/转义字符/************************************************************/
转义字符		释义
\?                     在书写连续多个问号时使用，防止他们被解析成三字母词
\`			用于表示字符常量`
\"			用于表示一个字符产内部的双引号
\\			用于表示一个反斜杠，防止它被解释为一个转义序列符
\a			警告字符，蜂鸣
\b			退格符
\f			换页
\n			换行
\r			回车
\t			水平制表符
\v			垂直制表符
\ddd		ddd表示1~3个八进制的数字。如：\130X
\xdd		dd表示2个十六进制数字。如 : \x30 0


