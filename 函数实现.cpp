

void* memcpy(void* dest, const void* src, size_t n) 
{
    unsigned char* d = dest;
    const unsigned char* s = src;

    // 从低地址到高地址逐字节复制
    while (n--) 
    {
        *d++ = *s++;
    }

    return dest;
}


void* memmove(void* dest, const void* src, size_t n) {
    unsigned char* d = dest;
    const unsigned char* s = src;

    // 如果目标内存区域在源内存区域的右侧（目标在源的后面）
    if (d > s && d < s + n) {
        // 从后往前复制
        d += n;
        s += n;
        while (n--) {
            *(--d) = *(--s);
        }
    }
    else {
        // 否则，可以从前往后复制
        while (n--) {
            *d++ = *s++;
        }
    }

    return dest;
}


void* memset(void* str, int c, size_t n) {
    unsigned char* ptr = str;
    unsigned char value = (unsigned char)c;  // 将传入的值转换为 unsigned char

    // 遍历内存区域并设置每个字节的值
    while (n--) {
        *ptr++ = value;
    }

    return str;
}


