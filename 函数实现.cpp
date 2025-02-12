

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


char* strcpy(char* dest, const char* src) {
    char* d = dest;
    while ((*d++ = *src++) != '\0') {
        // 复制 src 到 dest，遇到 '\0' 结束
    }
    return dest;
}


char* strncpy(char* dest, const char* src, size_t n) {
    char* d = dest;
    size_t i = 0;
    while (i < n && *src != '\0') {
        *d++ = *src++;
        i++;
    }
    // 若 n 超过 src 长度，用 '\0' 填充
    while (i++ < n) {
        *d++ = '\0';
    }
    return dest;
}


int strcmp(const char* str1, const char* str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(unsigned char*)str1 - *(unsigned char*)str2;
}


const char* strchr(const char* str, int c) {
    while (*str != '\0') {
        if (*str == (char)c) {
            return str;
        }
        str++;
    }
    return c == '\0' ? str : nullptr;
}


size_t strlen(const char* str) {
    const char* s = str;
    while (*s != '\0') {
        s++;
    }
    return s - str;
}







//链表
#include <iostream>
using namespace std;

// 链表节点定义
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

// 插入节点（头插法）
void insert(Node*& head, int value) {
    Node* newNode = new Node(value);
    newNode->next = head;
    head = newNode;
}

// 删除节点（按值删除，删除第一个匹配的节点）
bool deleteNode(Node*& head, int value) {
    if (!head) return false;

    Node* current = head;
    // 如果删除的是头节点
    if (current->data == value) {
        head = head->next;
        delete current;
        return true;
    }

    // 遍历寻找要删除的节点
    while (current->next && current->next->data != value) {
        current = current->next;
    }

    if (current->next) {
        Node* target = current->next;
        current->next = target->next;
        delete target;
        return true;
    }
    return false;
}

// 反转链表
Node* reverse(Node* head) {
    Node* prev = nullptr;
    Node* current = head;
    while (current) {
        Node* nextNode = current->next;
        current->next = prev;
        prev = current;
        current = nextNode;
    }
    return prev;
}

// 合并两个已排序的链表
Node* merge(Node* list1, Node* list2) {
    if (!list1) return list2;
    if (!list2) return list1;

    Node dummy(0); // 哨兵节点
    Node* tail = &dummy;

    while (list1 && list2) {
        if (list1->data <= list2->data) {
            tail->next = list1;
            list1 = list1->next;
        }
        else {
            tail->next = list2;
            list2 = list2->next;
        }
        tail = tail->next;
    }

    tail->next = list1 ? list1 : list2;
    return dummy.next;
}

// 打印链表
void printList(Node* head) {
    while (head) {
        cout << head->data << " -> ";
        head = head->next;
    }
    cout << "null" << endl;
}