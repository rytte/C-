

// placement new
什么是 placement new？
placement new 是 C++ 的一个特殊用法，用来在已经分配好的内存上直接调用构造函数，创建对象，而不是重新分配内存。

void* mem = std::malloc(sizeof(MyClass));  // 或从内存池拿内存
MyClass* p = new (mem) MyClass(args...);   // 这一步只调用构造函数，但内存是你提供的 mem，不会分配新内存。



