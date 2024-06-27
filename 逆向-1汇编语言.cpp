/********************/汇编/************************************************************/

//8086寄存器汇总
//通用寄存器：共有8个，每个都是16位。
AX：累加寄存器，用于算术运算。
BX：基地址寄存器，常用于存放基地址。
CX：计数器寄存器，用于字符串操作和循环计数。
DX：数据寄存器，常用于乘除运算和I / O操作。
SP：堆栈指针寄存器，指向当前栈的顶部。
BP：基指针寄存器，常用于指向当前栈的底部或其他数据段。
SI：源变址寄存器，常用于存放源操作数的偏移地址。
DI：目的变址寄存器，常用于存放目的操作数的偏移地址。
//控制寄存器：
IP：指令指针寄存器，存放程序当前指令在代码段的偏移位置。
FLAG：标志寄存器，用于存放指令执行后的状态信息，如进位、溢出等。
//段寄存器：共有4个，每个都是16位。
CS：代码段寄存器，存放程序代码段起始地址的高16位。
DS：数据段寄存器，存放数据段起始地址的高16位。
SS：堆栈段寄存器，存放堆栈段起始地址的高16位。
ES：附加段寄存器，存放扩展数据段起始地址的高16位。


//8086指令汇总
算术运算指令(会影响标志寄存器)
add
sub
adc
sbb
inc
dec
cmp
imul
idiv
aaa
数据传送指令
mov
push
pop
pushf
popf
xchg
逻辑指令
and
or
not
xor
test
shl
shr
sal
rol
ror
rcl
rcr
转移指令
无条件转移指令：jmp
条件转移指令：jcxz、je、jne、jb、ja、jnb、jna
循环指令：loop
过程：call、ret、retf
中断：int、iret
处理机控制指令(对标志寄存器或其他处理机进行设置)
cld
std
cli
sti
nop
clc
cmc
stc
hlt
wait
esc
lock
串处理指令，与rep、repe、repne等前缀指令配合使用
movsb
movsw
cmps
scas
lods
stos




/************************************************************/

//端序
计算机小端序：高位高地址，低位低地址

地址 1000 1001 1002 1003
数据	 0x12 0x34 0x56 0x78	(一个数据为一个字节大小，因为十六进制数据的一位表示二进制数据的四位)

从1001处取两个字节16bit数据，得到0x5634
程序存放顺序为低位到高位


//引言
8086的CPU只有16位，地址总线由有20位，因此会在内部使用 地址加法器 将两个16位地址合成一个20位地址
两个16位地址，一个称为段地址，一个称为偏移地址。物理地址 = 段地址 * 16 + 偏移地址。（物理地址 = 段地址:偏移地址）

偏移地址最大为16位(64K)，因此一个段的最大长度为64K

段地址存放在段寄存器：CS / DS / SS / ES



//CS和IP寄存器
CS存放段地址，IP存放偏移地址
CS : IP可以定位指令的地址


//DS寄存器
mov ax, 20			//20表立即数
mov ax, ds: [20]		//20表内存的偏移地址

段寄存器不能从内存取值，也不能用立即数赋值
mov ds, bx


//SS和SP寄存器
SS存放段地址，SP存放偏移指针
SS : SP可以定位栈顶的位置，从而实现PUSH和POP的操作

栈溢出问题(上溢 / 下溢)：没有预防机制，自己小心。

10000H "+---+" << SS = 1000H(栈底)（栈范围10000H~10002H）
10001H "+---+"
10002H "+---+"
10003H "+---+" << SP = 0003H(栈顶)（此时为栈空状态）（栈是从高地址向低地址增长的）


//汇编程序
汇编指令是有相应机器码的指令，由CPU执行
伪指令没有相应机器码，由编译器执行

【定义一个段】
段名 segment			//DOS中一般需要这么写
...
段名 ends

end：汇编程序结束标识
assume：(MASM编译器特有)将一个特定用途的段和相关的段寄存器关联起来。assume 段寄存器 : 段名


//[bx]
[bx]表示寄存器中的值是操作数所在内存的偏移地址
bx  表示寄存器中的值是操作数

以下写法等价，偏移地址为bx中的数值+200
mov ax, [bx+200]
mov ax, 200[bx]
mov ax, [bx].200


//loop 循环指令，短转移
loop 标签
(cx) = (cx)-1		//cx存放循环次数
判断cx值，不为0则跳转到标签处(开始下一轮循环)，若为0就向下执行

mov cx, 循环次数
s : 循环代码
...
loop s

loop指令就是jcxz指令每次执行前使cx-1


//ES寄存器
将一个数据从一个内存地址送往另一个相距64K(超出偏移地址上限)个单元地址时，需要对DS / CS / SS进行两次设置。
在循环结构中效率不高，此时可以使用ES寄存器作为另一根段地址使用，提高效率。


//dw(define word)
dw用于定义字型数据，目的是为待处理的数据在代码段中开辟存储空间存放。
也可以定义一些空数据0，将该内存作备用(如：作为栈使用)。
assume cs : code
code segment
dw 0123h, 0456h, 0789h, 0abch		//定义数据
start : move bx, 0					//start用于指明程序入口。否则IP会指向前面定义的数据。这个标签名由末尾的end决定。
		move ax, 0
		move cx, 4
	s : add ax, cs : [bx]
		add bx, 2					//因为是字型数据，所以每次加2个字节
		loop s

		mov ax, 4c00h
		int 21h
	code ends
end start

可执行文件 = 描述信息 + 程序（汇编指令和定义数据）
描述信息由编译器和链接器对相关伪指令的处理得到，如程序入口等信息。


//数据、代码、栈放入不同的段
assume cs : code, ds : data, ss : stack	//寄存器与段关联
data segment							//数据段
	dw 0123h, 0456h, 0789h, 0abch
data ends
stack segment							//栈段
	dw 0, 0, 0, 0
stack ends
code segment							//代码段
start:	mov ax, stack					//使用标签
		mov ss, ax
		mov sp, 20h
		mov ax, data
		mov ds, ax
		mov bx, 0
		mov cx, 8
	s:	push [bx]
		add bx, 2
		loop s
		mov bx, 0
		mov cx, 8
	s0:	pop [bx]
		add bx, 2
		loop s0
		
		mov ax, 4c00h
		int 21h
	code ends
end start

* 标签可以作为首地址使用。如数据data : 4就是0789h的地址，但它是一个常数，将其送入ds前需要经过ax中转。


//and和or指令
and ：逻辑与，按位进行与运算。
用法：可以将数据的相应位设为0。
例如：将al中数据的第3位设为0： and al, 11110111B

or ：逻辑或，按位进行或运算。
用法：可以将数据的相应位设为1。
例如：将al中数据的第3位设为1： and al, 00001000B

应用：可以在不判断ASCII值的情况下进行大小写转换（大写字母的第5位为0，小写为1）


//字符数据
字符数据使用单引号给出，如下
db 'unIX'			//相当于定义了四个字节型数据，等同于 db 75H, 6EH, 49H, 58H
mov al, 'a'			//等同于 mov al, 61H


//SI和DI寄存器
SI和DI原本被设计为字符串的操作，用法和bx相同（自增量i），他们分别指向源串和目的串，现在比较通用。

//[bx+si]和[bx+di]
以下写法等价, 偏移地址为bx中的数值+si中的数值
mov ax, [bx+si]
mov ax, [bx][si]

以下写法等价, 偏移地址为bx中的数值+si中的数值+200
mov ax, [bx+200+si]
mov ax, 200[bx][si]
mov ax, [bx].200[si]
mov ax, [bx][si].200


//小结
一般来说，暂存数据应该使用栈（内存）。

常数执行前，由CPU的指令缓冲器给出。

4个可以间接寻址的寄存器：bx、bp、si、di。均可单独使用。组合形式：[bx/bp + si/di + 数值]
含有bp的间址表达式中(如[bp+si+10])，如果没给定段地址ds，则默认段地址为ss

处理数据的长度取决于指令中最小的寄存器大小（如 mov ax, 100 就是字操作）
如果没有寄存器的话，要用伪指令给出大小（如 mov byte ptr [bx], 100 是字节操作）
push、pop等指令默认为字操作。


//寻址方式
数据(操作数)位置
{
	指令中(立即数寻址) : mov ax, 200h
	寄存器中(寄存器寻址) : mov ax, bx
	内存中
	{
		直接寻址: mov ax, [0x1001]
		寄存器间接寻址: mov ax, [bx]
		寄存器相对寻址: mov ax, [bx+100]
		基址变址寻址: mov ax, [bx+si]
		相对基址变址寻址: mov ax, [bx+si+100]
	}
}


//div 除法
div 除数(寄存器或内存单元)

（1）除数：有8位或16位，在一个寄存器或内存单元中
（2）被除数和结果
若除数8位，则被除数16位，默认在AX中。					  商放AL中，余数放AH中。
若除数16位，则被除数32位，默认在DX(高16位)和AX(低16位)中。商放AX中，余数放DX中。


//divdw 除法
divdw的商不会产生溢出
除数16位，被除数32位，商32位。
被除数和商：DX放高16位，AX放低16位。CX放余数。


//mul 乘法
两个数的位数要相同
mul 寄存器/内存单元
若是8位，则另一个操作数默认在AL中。结果放AX中。
若是16位，则另一个操作数默认在AX中。结果放DX和AX中（DX放高位，AX放低位）。


//dup 重复
dup与db/dw/dd等数据定义伪指令配合使用
db 重复次数 dup (重复的数据)
db 3 dup (0)				//定义了3个字节，值都是0，相当于db 0,0,0
db 3 dup (0,1,2)			//db 0,1,2,0,1,2,0,1,2
db 3 dup('abc', 'ABC')		//db 'abcABCabcABCabcABC' 共18字节


//转移指令分类
可以修改IP，或同时修改CS和IP的指令统称为转移指令。

段内转移：只修改IP		//如 jmp ax
{
	短转移：IP修改范围为 -128~127		  //2^7
	近转移：IP修改范围为 -32768~32767	  //2^15
}
段间转移：同时修改CS和IP	//如 jmp dword ptr [bx]

段内转移，编译后的机器码：是当前IP与目的地址的相对位置的补码
段间转移，编译后的机器码：是段地址和偏移地址的补码

转移距离超界编译器会报错


//转移指令
无条件转移指令(jmp)
条件转移指令
循环指令(loop)
过程
中断


//伪指令offset和seg
offset的作用是取得标号的偏移地址，如下：
start: mov ax, offset start	//相当于mov ax, 0
	s: mov ax, offset s		//相当于mov ax, 3  (第一条指令长度为3字节)

seg的作用是取得标号的段地址


//jmp
jmp short 标号	//短转移

start: mov ax, 0
	   jmp short s		//short s的机器码是下条指令(因为要先IP++)与标号s的相对位置0003H(八位位移、补码表示)，而非段偏移地址0008H
	   add ax, 1
	s: inc ax

jmp near ptr 标号	//近转移		IP=IP+16位位移补码(在编译时得到)

jmp far ptr 标号		//远转移，段间转移		far ptr 标号 的机器码指明标号的段地址和偏移地址

jmp 16位寄存器			//近转移，段内转移。仅修改IP
jmp ax

jmp word ptr 内存单元地址		//近转移，段内转移

jmp dword ptr 内存单元地址	//远转移，段间转移（高地址字是目的段地址，低地址字是目的偏移地址）
jmp dword ptr es:[1000H]
jmp dword ptr [bx]


//jcxz 有条件转移指令（短转移）（Jump if CX is Zero）
jcxz 标号		如果CX为0，则转移到标号处执行。(IP) = (IP)+8，补码表示
	

//ret和retf指令
ret指令用栈中的数据，修改IP的内容，从而实现近转移
ret 等价于 pop IP

retf指令用栈中的数据，修改CS和IP的内容，从而实现远转移
retf 等价于 pop IP、pop CS


//call指令
call指令将当前IP(近转移)或是CS和IP(远转移)压入栈中，然后执行转移到标号（jmp 标号）。//注意当前IP已经+1了。

call 标号					//近转移，只压入IP
即
push IP
jmp near ptr 标号

call far ptr 标号			//远转移，压入CS和IP
即
push CS
push IP
jmp far ptr 标号

call 16位寄存器				//近转移，只压入IP
即
push IP
jmp 16位寄存器

call word ptr 内存单元地址	//近转移，只压入IP
即
push IP
jmp word ptr 内存单元地址

call dword ptr 内存单元地址	//远转移，压入CS和IP
即
push CS
push IP
jmp dword ptr 内存单元地址


//参数和返回值的传递
单返回值：存在寄存器中
多返回值：存在内存中，寄存器放该内存首地址


//寄存器冲突
为了避免多个函数造成的寄存器冲突不够用的情况。
我们需要在子程序的开始将子程序中所有“用到的寄存器”中的内容保存起来，在程序返回前再恢复到寄存器。可以用栈来保存寄存器中的内容。

子程序开始：子程序中使用的寄存器入栈
		   子程序内容
		   子程序中使用的寄存器出栈
		   返回(ret/retf)


//标志寄存器FLAG
位		11 10 9  8  7  6  4  2  0
标志		OF DF IF TF SF ZF AF PF CF

置1条件
ZF（零标）：结果为0
PF（奇偶）：结果中1的个数为偶数
SF（符号）：结果为负
CF（进位）：结果的最高位有进位或借位		//无符号数运算时有意义
OF（溢出）：结果在寄存器中存不下（溢出）	//有符号数运算时有意义
DF（方向）：控制每次操作后di和si的增减		//0:操作后递增	1:操作后递减    对movsb和movsw指令有效
AF（辅助进位）：结果的第三位向第四位发生了进位或借位
IF（中断允许）：控制CPU是否响应外部中断
TF（调试）：当TF = 1时，处理器执行一条指令就进入中断，即单步执行。这通常用于调试目的。

cld指令：将DF位置0
std指令：将DF位置1
cli指令：将IF位置0
sti指令：将IF位置1

*一些指令不影响标志位，如：push、pop、inc、mov、loop等。

00000001B	可看作无符号数1，或有符号数+1
10000001B	可看作无符号数129，或有符号数-127

mov al, 10000001B
add al, 1			

若当作无符号数，运算: 129 + 1 = 130(10000010B 补)		//此时sf=0
若当作有符号数，运算: -127 + 1 = -126(10000010B 补)	//此时sf=1


//adc 带进位加法指令
adc 操作对象1, 操作对象2
结果：操作对象1 = 操作对象1 + 操作对象2 + CF
例如：adc ax, bx  //(ax)=(ax)+(bx)+CF


//sbb 带借位减法指令
sbb 操作对象1, 操作对象2
结果：操作对象1 = 操作对象1 - 操作对象2 - CF
例如：sbb ax, bx  //(ax)=(ax)-(bx)-CF


//cmp 比较指令
cmp 操作对象1, 操作对象2
cmp指令相当于减法指令，不保存结果，会对标志寄存器产生影响
其它相关指令通过被影响的标志寄存器位来得知比较结果（主要观察ZF与CF，SF与OF）


//条件转移指令
条件转移指令通过判断标志位进行转移，应配合cmp使用。

je		等于则转移		zf=1
jne		不等于则转移		zf=0
jb		低于则转移		cf=1
jnb		不低于则转移		cf=0
ja		高于则转移		cf=0且zf=0
jna		不高于则转移		cf=1或zf=1

n: not
e: equal
b: below
a: above


//movsb、movsw 串传送指令
这两个指令用于串的操作
movsb和movsw 功能：将ds:si指向的内存单元中的字节(字)送入es:di，然后根据df位的值，将si和di递增(+2)或递减(-2)

movsb相当于：
mov es:[di], byte ptr ds:[si]
inc si/dec si	//df=0为inc, df=1为dec
inc di/dec di

movsw相当于：
mov es : [di] , word ptr ds : [si]
add si, 2 / sub si, 2	//df=0为add, df=1为sub
add di, 2 / sub di, 2


//rep
movsb和movsw 通常和rep配合使用
rep：根据cx的值，重复执行后面的串传送指令movsb或movsw，实现(cx)个字符的传送

rep movsb
相当于：
s:movsb
  loop s


//pushf和popf
pushf: 将标志寄存器值压栈
popf:  从栈中弹出数据，送入标志寄存器中





