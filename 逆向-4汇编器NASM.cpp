//汇编器 MASM 和 NASM 对比
MASM	Windows，微软闭源，不支持输出bin格式
NASM	跨平台，社区开源，支持多种输出格式(bin、coff、omf、elf…)


assume ds : data                       section.data
data segment                           str : 'hello world!'
db 'hello word', 10;
data ends;


//语法特性
NASM：
1、区分大小写，如符号foo与FOO是两个不同的标识符。
2、访问内存需要使用[]将内存地址括起来，否则会被当作立即数。
3、不存储类型信息，需要使用特定大小的命令，如MOVSW。
4、没有ASSUME伪指令。
5、引用浮点寄存器的方式与MASM不同。
6、声明数据块的方式与MASM不同，例如使用resb代替dup。
MASM：
1、不区分大小写。
2、内存访问语法与NASM不同。
3、提供了丰富的宏和内存模型，如SMALL、COMPACT。


//NASM 伪指令
nasm 定义的 7 种数据 size
byte ： 8 位
word ： 16 位
dword ： 32 位
qword ： 64 位
tword ： 80 位
oword ： 128 位
yword ： 256 位

oword 可以对应 Microsoft MASM 的 xmmword 类型，yword 对应 Microsoft MASM 的 ymmword 类型。
tword, oword 以及 yword 使用在 非整型 数据，使用在 float 和 SSE 型数据。

定义初始化数据
db : define byte
dw ：define word
dd ：define doubleword
dq ：define quadword
dt ：define tword
do ：define oword
dy ：define yword

程序中使用到的非初始化数据通常放在 bss section 里，bss 代表 uninitialized storage space
NASM 使用了 resb （reserve byte） 家族来定义非初始化数据。
resb ：reserve byte
resw ：reserve word
resd ：reserve doubword
resq ：reserve quadword
rest ：reserve tword
reso ：reserve oword
resy ：reserve yword

包含 binary 文件
nasm 提供了一种包含 binary（二进制）文件的方法：使用 incbin 伪指令。incbin 伪指令包含的 binary 文件将直将写入输出文件中。此伪指令的作用是包含 graphics 以及 sound 这类数据文件。
incbin  "file.dat"; include the whole file
incbin  "file.dat", 1024; skip the first 1024 bytes
incbin  "file.dat", 1024, 512; skip the first 1024, and
; actually include at most 512


//equ 定义常量
equ 用来为标识符定义一个 整型 常量，它的作用类似 C 语言中的 #define
a  equ 0             // OK
b  equ 'abcd'        // OK! b = 0x64636261
c  equ 'abcdefghi'   // warning! c = 0x6867666564636261 整型常量最长为 quadword（8 bytes)
d  equ 1.2           // error! float不行


//使用 times 重复写数据或指令
times用来重复定义数据或指令。下面是一个经典的使用例子：
times 510-($-$$) db 0
dw 0xaa55
这段代码经常出现在 boot 磁盘 MBR 引导代码中，目的是除了最后 2 个字节和 code 代码外的区域全部写 0 值。

times 还可以使用在重复写某一条指令，如：times 10 nop
这段代码结果是重复填入了 10 条 nop 指令：
00000000  90                nop
00000001  90                nop
00000002  90                nop
00000003  90                nop
00000004  90                nop
00000005  90                nop
00000006  90                nop
00000007  90                nop
00000008  90                nop
00000009  90                nop


//整型常量
十进制的前缀是：0d, 后缀是：d, 或缺省。
十六进制的前缀是：0h 或 0x (c/c++ 风格，后缀是：h
八进制的前缀可以是：0o 或 0q 后缀可以是：o 或 q
二进制的前缀是：0b 后缀是：b


//字符常量
在 nasm 中，可以使用 3 种引号来提供字符
'...' （单引号）
"..." （双引号）
`...` （反引号）
如下示例，它们的结果是一样的：
db  'abcd'
db  "abcd"
db  `abcd`

//nasm 中的转义符必须要用 ` `（反引号）来引用
db  `/x61`		 //正确!'a'
db  '/x61'		 //错误!'/', 'x', '6', '1'

//八进制转义码
/ 后面最多可以跟着 3 位数字，构成八进制转义码，如下所示：
/ 004	; EOT
/ 006	; ACK
/ 025	; NAK
/ 0		; NULL


//十六进制转义码
十六进制转义码以 x 或 X 开头，如下所示：
db `/x61`; 'a'
db `/x61 / x62 / x63 / x64`; 'abcd'


//Unicode 字符串
nasm 定义了两个操作数符来定义 Unicode 字符串：

__utf16__
__utf32__
下面是 nasm 里的例子：

% define u(x) __utf16__(x)
% define w(x) __utf32__(x)

dw u('C:/WINDOWS'), 0; Pathname in UTF - 16
dd w(`A + B = / u206a`), 0; String in UTF - 32



//浮点数常量
浮点数变量可以使用 DB, DW, DD, DQ, DT 以及 DO ，
浮点数常量使用 __float8__, __float16__, __float32__, __float64__, __float80m__, __float80e__, __float128l__ 以及 __float128h__ 来定义。


//$和$$标号
$ 标号表示 nasm 编译后当前指令位置
$$ 标号表示当前 section 起始位置
例：
bits 64
section.rdata
dq 0
section.text
mov rax, 0
mov rax, $ - $$


//NASM 位运算符（与 C 一样）
位运算符		描述
&			位与: AND
|			位或：OR
~			位非 : NOT
^			位异或 : XOR
<<			左移
>>			右移


// NASM 支持的算术运算符
算术运算符	描述
+			加
-			减
*			乘
/			除（无符号数）
//			除（符号数）
%			取模（无符号数）
% %			取模（符号数）
