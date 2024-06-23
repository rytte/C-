
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
mov byte ptr [bx + 10h + si], 'A'           //dec.cp[i] = 'A'
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


int fun(int N)
{
    int ax = 2;
    do {
        ax = ax + ax;
        N--;
    } while (N != 0);
    return ax;
}

int main(void)
{
    int bx = fun(N)
        return 0;
}




