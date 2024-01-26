/********************/可变参数宏库/************************************************************/
#include <stdarg.h>

typedef char* va_list;          //va_list：可变参数列表

va_start，获取可变参数列表的第一个参数的地址（list是类型为va_list的指针，param1是可变参数最左边的参数）
#define va_start(list,param1)   ( list = (va_list)&param1+ sizeof(param1) )

va_arg，获取可变参数的当前参数，返回指定类型并将指针指向下一参数（mode参数描述了当前参数的类型）
#define va_arg(list,mode)   ( (mode *) ( list += sizeof(mode) ) )[-1]

va_end，清空va_list可变参数列表
#define va_end(list) ( list = (va_list)0 )

va_copy，拷贝va_list的内容
#define va_copy(destination, source)  ((destination) = (source))

注：以上sizeof()只是为了说明工作原理，实际实现中，增加的字节数需保证为为int的整数倍
如：#define _INTSIZEOF(n) ((sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1))

C语言中函数参数是存储在栈中的，从右往左依次入栈。存储空间为连续存储，且参数按照固定字节对齐；


实例1：
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

void var_test(const char* format, ...)
{
        va_list list;
        va_start(list, format);                           //将format赋给list

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
        va_end(list);                                          //清空va_list参数列表
}

int main()
{
        var_test("test", "this", "is", "a", "test", "");                 //this is a test
        return 0;
}





实例2：定制错误打印函数error

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



/********************/printf()/************************************************************/
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
        n = vsprintf(sprint_buf, fmt, args);    // 根据字符串fmt，将对应形参转换为字符串，并组合成新的字符串存储在sprint_buf[]缓存中，返回字符个数。
        va_end(args);                                    //c标准要求在同一个函数中va_start 和va_end 要配对的出现。
        
//        if (console_ops.write)                                  // 调用相关驱动接口,将sprintf_buf中的内容输出n个字节到设备，
//                console_ops.write(sprint_buf, n);        // 此处可以是串口、控制台、Telnet等,在嵌入式开发中可以灵活挂接
        return n;
}


常见组合及输出结果

int main(void)
{
        int a = 10, b = 3;
        printf("%*.*d\n", a, b, -100);          //              -100    //输出数字，右对齐,宽度从变量获取
        printf("%10.3d\n", -100);              //               -100    //输出数字，右对齐
        printf("%-10.3d\n", -100);             // -100                  //输出数字，左对齐
        printf("%+10.3d\n", 100);             //                +100  //输出数字，正数带正号
        printf("%0.13d\n", 100);               // 0000000000100//输出文本格式,如员工号
        printf("%#.8x\n", 0x30ff);             // 0x000030ff        //输出8位16进制地址，小写字母
        printf("%#.8X\n", 0x30ff);             // 0X000030FF      //输出8位16进制地址，大写字母
        printf("%.3f\n", 3.14159267892); // 3.142                  //保留浮点小数点后有效位数
        printf("%llu\n", 0xffffffffffffffff);   // 18446744073709551615//输出64位长整型
}



/********************/scanf()/************************************************************/
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




/********************/格式控制符/************************************************************/
格式字符		意义
% a, % A		十六进制浮点数（C99 新增）。//实例 printf("pi=%a\n", 3.14); 输出 pi = 0x1.91eb86p+1。
% d			十进制有符号整数（正数不输出正号）
% o			八进制无符号整数（不输出前缀0）
% x, % X		十六进制无符号整数（不输出前缀0x）
% u			十进制无符号整数
% f			小数形式单、双精度实数
% e, % E		指数形式单、双精度实数
% g, % G		以% f或% e中较短的输出宽度输出单、双精度实数
% c			单个字符
% s			字符串
% p			指针地址
% lu			32位无符号整数
% llu			64位无符号整数
% %                 不转换参数，输出字符%



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
\ddd			ddd表示1~3个八进制的数字。如：\130X
\xdd			dd表示2个十六进制数字。如 : \x30 0







vsprintf解析模式详解
vsprintf采用% [flags][width][.prec][length][type]模式对各个参数进行解析各标志解析如下表：

标志（flags）

标志（flags）用于规定输出样式，含义如下：

flags（标志）       字符名称            描述

-                           减号                  在给定的字段宽度内左对齐，右边填充空格（默认右对齐）

+

加号

强制在结果之前显示加号或减号（ + 或 - ），即正数前面会显示 + 号；默认情况下，只有负数前面会显示一个 - 号

（空格）

空格

输出值为正时加上空格，为负时加上负号

#

井号

specifier 是 o、x、X 时，增加前缀 0、0x、0X；

specifier 是 e、E、f、g、G 时，一定使用小数点；

specifier 是 g、G 时，尾部的 0 保留

0

数字零

对于所有的数字格式，使用前导零填充字段宽度（如果出现了减号标志或者指定了精度，则忽略该标志）

最小宽度（width）

最小宽度（width）用于控制显示字段的宽度，即打印输出的总宽度，取值和含义如下：

width（最小宽度）

字符名称

描述

digit(n)

数字

字段宽度的最小值，如果输出的字段长度小于该数，结果会用前导空格填充；如果输出的字段长度大于该数，结果使用更宽的字段，不会截断输出

*

星号

宽度在 format 字符串中规定位置未指定，使用星号标识附加参数，指示下一个参数是width

精度（.prec）

精度（.precision）用于指定输出精度，即输出数据占用的宽度，取值和含义如下：

.pre（精度）

字符名称

描述

.digit(n)

点 + 数字

对于整数说明符（d、i、o、u、x、X）：precision 指定了要打印的数字的最小位数。如果写入的值短于该数，结果会用前导零来填充。如果写入的值长于该数，结果不会被截断。精度为 0 意味着不写入任何字符；

对于 e、E 和 f 说明符：要在小数点后输出的小数位数；

对于 g 和 G 说明符：要输出的最大有效位数；

对于 s 说明符：要输出的最大字符数。默认情况下，所有字符都会被输出，直到遇到末尾的空字符；

对于 c 说明符：没有任何影响；

当未指定任何精度时，默认为 1。如果指定时只使用点而不带有一个显式值，则标识其后跟随一个 0。

.*

点 + 星号

精度在 format 字符串中规定位置未指定，使用点 + 星号标识附加参数，指示下一个参数是精度

类型长度（length）

类型长度（length）用于控制待输出数据的数据类型长度，取值和含义如下：

length（类型长度）

描述

h

参数被解释为短整型或无符号短整型（仅适用于整数说明符：i、d、o、u、x 和 X）

l

参数被解释为长整型或无符号长整型，适用于整数说明符（i、d、o、u、x 和 X）及说明符 c（表示一个宽字符）和 s（表示宽字符字符串）

ll

参数被解释为超长整型或无符号超长长整型，适用于整数说明符（i、d、o、u、x 和 X）及说明符 c（表示一个宽字符）和 s（表示宽字符字符串）
