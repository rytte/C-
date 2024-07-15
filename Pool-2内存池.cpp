/********************/内存池/************************************************************/


内存池（Memory Pool）是一种优化内存分配和释放的技术，通过预先分配一大块内存并在其中进行小块内存的分配和释放，减少内存碎片，提高内存分配效率。


#include <iostream>
#include <vector>
#include <cstddef>

class MemoryPool {
public:
    MemoryPool(size_t chunkSize, size_t poolSize)
        : chunkSize(chunkSize), poolSize(poolSize), memory(nullptr), freeList(nullptr) {
        allocatePool();
    }

    ~MemoryPool() {
        delete[] memory;
    }

    void* allocate() {
        if (freeList == nullptr) {
            allocatePool();
        }
        void* freeChunk = freeList;
        freeList = *reinterpret_cast<void**>(freeList);
        return freeChunk;
    }

    void deallocate(void* ptr) {
        *reinterpret_cast<void**>(ptr) = freeList;
        freeList = ptr;
    }

private:
    void allocatePool() {
        memory = new char[chunkSize * poolSize];
        freeList = memory;

        for (size_t i = 0; i < poolSize - 1; ++i) {
            char* next = memory + (i + 1) * chunkSize;
            *reinterpret_cast<void**>(memory + i * chunkSize) = next;
        }
        *reinterpret_cast<void**>(memory + (poolSize - 1) * chunkSize) = nullptr;
    }

    size_t chunkSize;    // 每块内存的大小
    size_t poolSize;     // 内存池的块数
    char* memory;        // 内存池
    void* freeList;      // 空闲块链表
};

int main() {
    const size_t chunkSize = 32;  // 每块内存的大小
    const size_t poolSize = 10;   // 内存池的块数

    MemoryPool pool(chunkSize, poolSize);

    // 分配几个块
    void* ptr1 = pool.allocate();
    void* ptr2 = pool.allocate();
    void* ptr3 = pool.allocate();

    std::cout << "Allocated addresses: " << ptr1 << ", " << ptr2 << ", " << ptr3 << std::endl;

    // 释放块
    pool.deallocate(ptr1);
    pool.deallocate(ptr2);
    pool.deallocate(ptr3);

    // 再次分配
    void* ptr4 = pool.allocate();
    void* ptr5 = pool.allocate();

    std::cout << "Reallocated addresses: " << ptr4 << ", " << ptr5 << std::endl;

    return 0;
}



//解释
1、内存池类 MemoryPool：
* chunkSize：每块内存的大小。
* poolSize：内存池的块数。
* memory：指向内存池的指针。
* freeList：空闲块链表的头指针。

2、构造函数和析构函数：
* 构造函数 MemoryPool(size_t chunkSize, size_t poolSize) 初始化块大小和池大小，并调用 allocatePool() 分配内存池。
* 析构函数 ~MemoryPool() 释放内存池。

3、内存分配函数 allocate()：
* 如果 freeList 为空，表示没有可用的内存块，调用 allocatePool() 分配新的内存池。
* 从 freeList 中取出一个块，并更新 freeList 指向下一个空闲块。
* 返回分配的内存块。

4、内存释放函数 deallocate(void* ptr)：
* 将释放的内存块插入 freeList，使其成为新的空闲块头。

5、私有方法 allocatePool()：
* 分配内存池，并将其分割成多个小块，构建空闲块链表。

6、主函数 main()：
* 创建一个 MemoryPool 对象，指定块大小和池大小。
* 分配几个块并打印其地址。
* 释放块后再次分配并打印其地址。

通过这种方式，可以有效地减少频繁的小块内存分配和释放带来的开销和内存碎片问题。