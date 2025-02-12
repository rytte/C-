#include <iostream>
#include <vector>
#include <cstring> // for memset

#define MEMORY_POOL_SIZE 1024  // 简化版本总内存大小
#define BLOCK_SIZE 32          // 每块固定大小

class SimpleMemoryAllocator {
private:
    unsigned char memoryPool[MEMORY_POOL_SIZE]; // 模拟内存池
    bool blockStatus[MEMORY_POOL_SIZE / BLOCK_SIZE]; // 每个块的使用状态

public:
    SimpleMemoryAllocator() {
        memset(memoryPool, 0, sizeof(memoryPool));
        memset(blockStatus, 0, sizeof(blockStatus));
    }

    void* malloc(size_t size) {
        // 简化：只允许分配 BLOCK_SIZE 大小倍数的内存
        size_t numBlocks = (size + BLOCK_SIZE - 1) / BLOCK_SIZE;

        // 寻找连续空闲块
        for (size_t i = 0; i <= (MEMORY_POOL_SIZE / BLOCK_SIZE - numBlocks); ++i) {
            bool found = true;
            for (size_t j = 0; j < numBlocks; ++j) {
                if (blockStatus[i + j]) {  // 该块已被使用
                    found = false;
                    break;
                }
            }

            if (found) { // 找到合适的连续内存块
                for (size_t j = 0; j < numBlocks; ++j) {
                    blockStatus[i + j] = true;
                }
                return memoryPool + i * BLOCK_SIZE;
            }
        }

        std::cerr << "Error: Not enough memory!" << std::endl;
        return nullptr;
    }

    void free(void* ptr) {
        if (!ptr) return;

        size_t offset = (unsigned char*)ptr - memoryPool;
        if (offset >= MEMORY_POOL_SIZE || offset % BLOCK_SIZE != 0) {
            std::cerr << "Error: Invalid pointer!" << std::endl;
            return;
        }

        size_t blockIndex = offset / BLOCK_SIZE;

        // 释放连续块
        while (blockIndex < MEMORY_POOL_SIZE / BLOCK_SIZE && blockStatus[blockIndex]) {
            blockStatus[blockIndex] = false;
            ++blockIndex;
        }
    }

    void showMemoryStatus() {
        std::cout << "Memory Blocks Status: ";
        for (bool status : blockStatus) {
            std::cout << (status ? "[X]" : "[ ]");
        }
        std::cout << std::endl;
    }
};

int main() {
    SimpleMemoryAllocator allocator;

    // 分配内存示例
    void* p1 = allocator.malloc(64);
    allocator.showMemoryStatus();

    void* p2 = allocator.malloc(96);
    allocator.showMemoryStatus();

    // 释放内存示例
    allocator.free(p1);
    allocator.showMemoryStatus();

    allocator.free(p2);
    allocator.showMemoryStatus();

    return 0;
}
