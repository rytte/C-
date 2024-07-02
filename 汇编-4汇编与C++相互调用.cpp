/********************/内嵌汇编/************************************************************/
汇编语言内嵌方式是特定于编译器的，不同的编译器可能具有不同的语法和约束。


// MSVC：__asm 关键字
#include <iostream>

int main() 
{
    int a = 5;
    int b = 10;
    int result;

    __asm {
        // 汇编代码
        mov eax, a     // 将 a 的值移动到寄存器 eax
        add eax, b     // 将 b 的值加到 eax
        mov result, eax  // 将 eax 的值移动到 result
    }

    std::cout << "Sum: " << result << std::endl;

    return 0;
}


// GCC：asm 关键字
#include <iostream>

int main() 
{
    int a = 5;
    int b = 10;
    int result;

    // 使用内嵌汇编计算两个数的和
    asm("add %[input1], %[input2];"   // 将 input1 与 input2 相加
        : [output] "=r" (result)      // 输出寄存器约束，将结果存储到 result 变量
        : [input1] "r" (a),           // 输入寄存器约束，将 a 存储到 input1
        [input2] "r" (b)            // 输入寄存器约束，将 b 存储到 input2
    );

    std::cout << "Sum: " << result << std::endl;

    return 0;
}



/********************/调用汇编函数/************************************************************/

//1.配置asm文件
新建.asm文件，右键该文件 >> 属性 >> 常规 >> 从生成中排除:否；项类型:自定义生成工具（或者Microsoft Macro Assembler，以下就不用配置了）
自定义生成工具 >> 常规：（以下不带双引号）
命令行："ml64 /Fo $(IntDir)%(fileName).obj /c %(fileName).asm"
输出："$(IntDir)%(fileName).obj"

给Asm文件添加函数代码


//2.编写汇编函数代码
.data

.const

.code

addNumber proc

mov rax, rcx    ; 将第一个参数的值加载到 rax
add rax, rdx    ; 将第二个参数的值加到 rax 上
ret
addNumber endp
end



//3.C/C++调用asm的函数
#include <iostream>

using namespace std;
extern "C" long long __stdcall addNumber(int, int);

int main()
{
    cout << "调用汇编函数加法 10 + 5 = " << addNumber(10, 5) << endl;
    system("pause");

    return 0;
}

如果你的工程比较大，那么你可以为你的64asm汇编文件添加一个头文件，
头文件中进行函数声明，以C方式导出，
你的CPP文件中包含这个头文件即可。



/********************/汇编调用C++函数/************************************************************/

调用Windows Api


//Cpp中导出调用
extern "C" void callMessageBox();


//汇编
.data

g_Title db "HelloWorld", 0
g_Text db  "xxx", 0

.const

.code

extrn MessageBoxA : proc;

callMessageBox PROC

sub rsp, 28h
xor r9, r9;
lea r8, g_Title;
lea rdx, g_Text
xor rcx, rcx
call MessageBoxA;
add rsp, 28h
ret
callMessageBox endp
end

//main函数中调用
callMessageBox();
