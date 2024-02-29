#include <iostream>
#include <list>
#include <vector>

using namespace std;

// 图的顶点类
class Vertex 
{
public:
        int id;
        Vertex(int id) : id(id) {}
};

// 图类
class Graph 
{
private:
        int numVertices;
        vector<list<Vertex*>> adjList;

public:
        Graph(int numVertices) : numVertices(numVertices) 
        {
                adjList.resize(numVertices);
        }

        // 添加边
        void addEdge(int src, int dest) 
        {
                Vertex* destVertex = new Vertex(dest);
                adjList[src].push_back(destVertex);
                // 如果是无向图，还需要添加 dest 到 src 的边
                // Vertex* srcVertex = new Vertex(src);
                // adjList[dest].push_back(srcVertex);
        }

        // 打印图
        void printGraph() 
        {
                for (int i = 0; i < numVertices; ++i) 
                {
                        cout << "顶点 " << i << " 的邻接顶点: ";
                        for (Vertex* v : adjList[i]) 
                        {
                                cout << v->id << " ";
                        }
                        cout << endl;
                }
        }
};

int main() 
{
        Graph g(5);

        // 添加边
        g.addEdge(0, 1);
        g.addEdge(0, 4);
        g.addEdge(1, 2);
        g.addEdge(1, 3);
        g.addEdge(1, 4);
        g.addEdge(2, 3);
        g.addEdge(3, 4);

        // 打印图
        g.printGraph();

        return 0;
}


在这个示例中，Graph 类表示一个图，其中 adjList 是一个存储了每个顶点的邻接列表的向量。
Vertex 类表示图中的顶点，其中 id 是顶点的标识符。
addEdge 方法用于向图中添加边，printGraph 方法用于打印图的邻接列表。


