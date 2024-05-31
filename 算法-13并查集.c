#include <stdio.h>
#include <stdlib.h>

// 定义并查集结构体
typedef struct
{
        int* parent;
        int size;
} UnionFind;

// 初始化并查集
UnionFind* createUnionFind(int size)
{
        UnionFind* uf = (UnionFind*)malloc(sizeof(UnionFind));
        uf->parent = (int*)malloc(size * sizeof(int));
        uf->size = size;
        for (int i = 0; i < size; ++i)
        {
                uf->parent[i] = i; // 每个节点的父节点初始化为自身
        }
        return uf;
}

// 查找节点所属的集合（根节点）
int find(UnionFind* uf, int x)
{
        if (uf->parent[x] != x)
        {
                uf->parent[x] = find(uf, uf->parent[x]); // 路径压缩
        }
        return uf->parent[x];
}

// 合并两个节点所属的集合
void merge(UnionFind* uf, int x, int y)
{
        int rootX = find(uf, x);
        int rootY = find(uf, y);
        if (rootX != rootY)
        {
                uf->parent[rootX] = rootY;
        }
}

// 检查两个节点是否属于同一集合
int isConnected(UnionFind* uf, int x, int y)
{
        return find(uf, x) == find(uf, y);
}

// 释放并查集内存
void destroyUnionFind(UnionFind* uf)
{
        free(uf->parent);
        free(uf);
}

int main() {
        int n = 6; // 节点数量
        UnionFind* uf = createUnionFind(n);

        // 添加一些连接
        merge(uf, 0, 1);
        merge(uf, 1, 2);
        merge(uf, 3, 4);

        // 检查连接情况
        printf("Node 0 and Node 2 are connected? %s\n", isConnected(uf, 0, 2) ? "Yes" : "No");
        printf("Node 0 and Node 5 are connected? %s\n", isConnected(uf, 0, 5) ? "Yes" : "No");

        // 释放内存
        destroyUnionFind(uf);

        return 0;
}
