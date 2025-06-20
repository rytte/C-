
汇编语言的难处在于只有少数个寄存器可以处理数据，经常需要使用内存保存数据，而内存又需要明确的地址。（编程时先定位内存地址到寄存器，再以C方式编码）
而高级语言，可以定义任意个变量，通过变量名定位地址。


//数组处理的对比
#include <stdio.h>

char a[5] = "BaSic";
char b[5] = "MinIX";

int main()
{
    int i;
    i = 0;
    do {
        a[i] = a[i] & 0xDF;
        b[i] = b[i] | 0x20;
        i++;
    } while (i < 5);
}


数据段
datasg:
db 'BaSic'              //a[5]
db 'MinIX'              //b[5]
代码段
mov ax, datasg
mov ds, ax
mov bx, 0               //i=0
mov cx, 5               //i<5
s:mov al, 0[bx]         //do    取a[i]到寄存器al
and al, 11011111b       //a[i]=a[i]&0xDF;
mov 0[bx], al           //寄存器al值放回a[i]
mov al, 5[bx]
or al, 00100000b
mov 5[bx], al
inc bx                  //i++
loop s                  //while


比较
C语言：a[i], b[i]
汇编： 0[bx], 5[bx]

说明：数组名表示地址，bx常用于自增变量i



//结构体处理的对比
任务：将位于内存seg:60的结构体，其排名改为38（结构体内偏移0CH），收入增加70（偏移0EH），著名产品“PDP”改为“VAX”（偏移10H）;
struct company 
{
    char cn[3];     /*公司名称*/
    char hn[9];     /*总裁姓名*/
    int pm;         /*排名*/
    int sr;         /*收入*/
    char cp[3];     /*著名产品*/
};
struct company dec = { "DEC", "Ken Olsen", 137, 40, "PDP" };

int main()
{
    int i;
    dec.pm = 38;
    dec.sr = dec.sr + 70;
    i = 0;
    dec.cp[i] = 'V';
    i++;
    dec.cp[i] = 'A';
    i++;
    dec.cp[i] = 'X';
    return 0;
}


mov ax, seg                      //先定位内存地址到寄存器（将ds与bx设置为结构体地址）
mov ds, ax
mov bx, 60h
                                 //C语言方式编程
mov word ptr[bx + 0ch], 38                  //dec.pm = 38;
mov word ptr[bx + 0eh], 70                  //dec.sr = dec.sr + 70;

mov si, 0                                   //i = 0;
mov byte ptr [bx + 10h + si], 'V'           //dec.cp[i] = 'V';
inc si                                      //i++
mov byte ptr [bx + 10h + si], 'A'           //dec.cp[i] = 'A';
inc si                                      //i++
mov byte ptr [bx + 10h + si], 'X'           //dec.cp[i] = 'X';


比较
C语言：dec.pm          dec.sr          dec.cp[i]
汇编： [bx].0ch        [bx].0eh        [bx].10h[si]



//计算2的N次方
start: mov ax, 1
       mov cx, N
       call fun
       mov bx, ax
       mov ax, 4c00h
       int 21h
  fun: add ax, ax       
       loop s
       ret


int fun(int cx)
{
    int ax = 2;
    do {
        ax = ax + ax;
        cx--;
    } while (cx != 0);
    return ax;
}

int main(void)
{
    int cx = N;
    int bx = fun(cx)
        return 0;
}



//函数栈
#include <iostream>  

int add(int, int);

int main(int argc, char* argv[])
{
    int a = 1;
    int b = 2;
    int c = 0;
    c = add(a, b);
}

int add(int a, int b)
{
    return a + b;
}


main:
    push    rbp                         //将上一函数的基址BP压栈             
    mov     rbp, rsp                    //将BP赋值为新函数的基址(新函数栈帧的栈底)
    sub     rsp, 32                     //SP指针下移32个字节（与BP间距32字节，是整个函数栈空间）
    mov     DWORD PTR[rbp - 20], edi    //DI(即参数1:argc) 压栈
    mov     QWORD PTR[rbp - 32], rsi    //SI(即参数2:**argv) 压栈
    mov     DWORD PTR[rbp - 4], 1       //第一个定义的变量a 压栈
    mov     DWORD PTR[rbp - 8], 2       //第二个定义的变量b 压栈
    mov     DWORD PTR[rbp - 12], 0      //第三个定义的变量c 压栈
    mov     edx, DWORD PTR[rbp - 8]     //b送入DX
    mov     eax, DWORD PTR[rbp - 4]     //a送入AX
    mov     esi, edx                    //b送入SI 调用参数
    mov     edi, eax                    //a送入DI 调用参数
    call    add(int, int)               //调用，压入IP值
    mov     DWORD PTR[rbp - 12], eax    //结果送到第三个变量c
    mov     eax, 0                      //AX清零
    leave                               //mov esp,ebp; 使SP也指向main的栈底BP
    ret                                 //结束
add(int, int) :
    push    rbp                         //将上一函数main的基址BP压栈
    mov     rbp, rsp                    //将BP赋值为新函数的基址(新函数栈帧的栈底)
    mov     DWORD PTR[rbp - 4], edi     //形参1(即a)压栈
    mov     DWORD PTR[rbp - 8], esi     //形参2(即b)压栈
    mov     edx, DWORD PTR[rbp - 4]     //a送入DX 使用形参a
    mov     eax, DWORD PTR[rbp - 8]     //b送入AX 使用形参b
    add     eax, edx                    //计算a+b，结果留在AX中
    pop     rbp                         //此时SP指向新函数栈帧的栈底，执行pop使BP指向main栈底(60)
    ret                                 //保存的IP值弹回IP寄存器


高地址(栈底)  
SS
60              BP
|  上一函数的BP   
56  
|  第一个变量
52  
|  第二个变量
48  
|  第三个变量
44  
|
40 
|  参数1
36  
|  参数2
32  
|  (参数2)
28              SP
|  call调用时的IP
24  
|  main函数的BP
20  
|  形参1
16  
|  形参2
8   
| 
4   
|
0   低地址(栈顶)


SS、SP和BP三个寄存器通常一起使用来确定堆栈中某一单元的地址。

SS：存放栈的段地址。SS:[0]
BP：定位当前函数栈帧的基地址。SS:[BP]
SP：定位当前指针具体位置。SS:[BP+SP]


//栈帧模型
栈通常是向下增长的（从高地址向低地址）

高地址(栈底)
+ ------------------ - +
| 返回地址(IP)          | < -返回地址存储在这里(call函数的下一条指令)
+ ------------------ - +
| 上一层栈帧的(BP)      | < -当前函数栈基址(enter)
+ ------------------ - +
| 局部变量1             | < -局部变量按定义顺序存储在这里(先定义的变量越靠上)
| 局部变量2             |
+ ------------------ - +
| 未使用区域            | < -栈帧大小为16Byte的整倍数，因此可能产生未使用区域
+ ------------------ - +
| 保存的寄存器          | < -调用其它函数前，将必要的寄存器值保存
+ ------------------ - +
| 形参1                | < -函数参数从这里开始存储(列表中越靠前的越靠上)
| 形参2                |
+ ------------------ - +
低地址(栈顶)


