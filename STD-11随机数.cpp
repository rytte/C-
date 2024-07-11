/********************/随机数/************************************************************/
#include <random>


随机数引擎（Generators）：负责生成随机数的算法;
std::mt19937 是一个基于Mersenne Twister算法的随机数生成器，非常常用。

随机数分布（Distributions）：定义了随机数的范围和类型;
std::uniform_int_distribution<>     生成指定范围内的均匀分布的整数;
std::uniform_real_distribution<>    生成指定范围内的均匀分布的浮点数;
std::normal_distribution<>          生成正态分布的浮点数;


//实例
#include <iostream>  
#include <random>  

int main() {
    // 创建一个随机数引擎  
    std::random_device rd;      // 真实随机数源（种子），用于初始化随机数引擎  
    std::mt19937 gen(rd());     // 以rd()作为种子初始化Mersenne Twister随机数生成器  

    // 创建一个随机数分布，这里是1到100之间的均匀分布  
    std::uniform_int_distribution<> dis(1, 100);

    // 生成10个随机数  
    for (int n = 0; n < 10; ++n) {
        // 使用随机数引擎和分布来生成随机数  
        std::cout << dis(gen) << ' ';
    }
    std::cout << '\n';

    return 0;
}


//注意
* 尽量避免直接使用std::rand()和srand()，因为它们生成的随机数质量较差，且不够灵活。
* 使用<random>库时，请确保每次程序运行时都使用不同的种子（如上例中的std::random_device），以避免生成相同的随机数序列。
* 不同的随机数引擎和分布可以组合使用，以满足不同的需求。


//扩展
xorshift 异或随机算法
