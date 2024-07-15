/********************/缓存池/************************************************************/


缓存池（Cache Pool）是一种用于高效管理内存缓存的设计模式。
它通过预先分配一块内存，并在其中进行小块内存的分配和释放，从而减少内存碎片和分配开销。


#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>

class CachePool {
public:
    CachePool(size_t chunkSize, size_t poolSize)
        : chunkSize(chunkSize), poolSize(poolSize), memory(nullptr) {
        allocatePool();
    }

    ~CachePool() {
        delete[] memory;
    }

    void* allocate() {
        if (freeList.empty()) {
            allocatePool();
        }
        void* freeChunk = freeList.front();
        freeList.pop_front();
        return freeChunk;
    }

    void deallocate(void* ptr) {
        freeList.push_back(ptr);
    }

    size_t getChunkSize() const {
        return chunkSize;
    }

private:
    void allocatePool() {
        memory = new char[chunkSize * poolSize];
        for (size_t i = 0; i < poolSize; ++i) {
            freeList.push_back(memory + i * chunkSize);
        }
    }

    size_t chunkSize;                 // 每块内存的大小
    size_t poolSize;                  // 内存池的块数
    char* memory;                     // 内存池
    std::list<void*> freeList;        // 空闲块链表
};

template <typename K, typename V>
class Cache {
public:
    Cache(size_t capacity, size_t chunkSize, size_t poolSize)
        : capacity(capacity), pool(chunkSize, poolSize) {}

    V* get(const K& key) {
        auto it = cacheMap.find(key);
        if (it != cacheMap.end()) {
            cacheList.splice(cacheList.begin(), cacheList, it->second.second);
            return it->second.first;
        }
        return nullptr;
    }

    void put(const K& key, const V& value) {
        auto it = cacheMap.find(key);
        if (it != cacheMap.end()) {
            cacheList.splice(cacheList.begin(), cacheList, it->second.second);
            *(it->second.first) = value;
        }
        else {
            if (cacheMap.size() == capacity) {
                auto last = cacheList.back();
                cacheList.pop_back();
                pool.deallocate(cacheMap[last].first);
                cacheMap.erase(last);
            }
            void* chunk = pool.allocate();
            V* valuePtr = new(chunk) V(value);
            cacheList.push_front(key);
            cacheMap[key] = { valuePtr, cacheList.begin() };
        }
    }

private:
    size_t capacity;                             // 缓存容量
    CachePool pool;                              // 缓存池
    std::list<K> cacheList;                      // 缓存键列表
    std::unordered_map<K, std::pair<V*, typename std::list<K>::iterator>> cacheMap; // 缓存映射
};

int main() {
    Cache<int, std::string> cache(3, sizeof(std::string), 10);

    cache.put(1, "value1");
    cache.put(2, "value2");
    cache.put(3, "value3");

    auto v1 = cache.get(1);
    if (v1) std::cout << "Key 1: " << *v1 << std::endl;

    cache.put(4, "value4");

    auto v2 = cache.get(2);
    if (v2) {
        std::cout << "Key 2: " << *v2 << std::endl;
    }
    else {
        std::cout << "Key 2 not found" << std::endl;
    }

    return 0;
}


//解释
1、缓存池类 CachePool：
* CachePool(size_t chunkSize, size_t poolSize) 构造函数初始化块大小和池大小，并调用 allocatePool() 分配内存池。
* ~CachePool() 析构函数释放内存池。
* allocate() 方法从 freeList 中获取一个块，如果 freeList 为空，则调用 allocatePool() 分配新的内存池。
* deallocate(void* ptr) 方法将块释放回 freeList。
* getChunkSize() 方法返回每块内存的大小。

2、私有方法 allocatePool()：
* 分配内存池，并将其分割成多个小块，构建空闲块链表。

3、缓存类 Cache：
* Cache(size_t capacity, size_t chunkSize, size_t poolSize) 构造函数初始化缓存容量，并创建缓存池。
* get(const K& key) 方法从缓存中获取指定键的值，并将其移到缓存列表的头部。
* put(const K& key, const V& value) 方法将值放入缓存中，如果缓存已满，则移除最久未使用的键值对。

4、主函数 main()：
* 创建一个容量为 3 的缓存，块大小为 sizeof(std::string)，池大小为 10。
* 插入几个键值对并获取其值。
* 插入新键值对并获取其值，验证缓存替换策略。
* 通过这种方式，缓存池可以高效地管理内存，提高缓存性能。



