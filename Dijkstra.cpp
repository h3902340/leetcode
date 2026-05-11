#include "Jutil.h"
using namespace std;

struct Data
{
    int v;
    int w;
};

// CSR Graph
const int N = 5e4;
const int M = 1e5;
class CSRGraph
{
    int eCnt;

public:
    Data to[M << 1];
    int nxt[M << 1];
    int head[N];
    void init(int n)
    {
        eCnt = 0;
        for (int i = 0; i < n; i++)
        {
            head[i] = -1;
        }
    }
    void addEdge(int u, int v, int w)
    {
        to[eCnt] = {v, w};
        nxt[eCnt] = head[u];
        head[u] = eCnt++;
    }
};

// Dijkstra
int dis[N];
bool vis[N];
auto cmp = [](Data &a, Data &b)
{ return a.w > b.w; };
void dijkstra(CSRGraph &g, int u, int n)
{
    priority_queue<Data, vector<Data>, decltype(cmp)> pq(cmp);
    for (int i = 0; i < n; i++)
    {
        dis[i] = -1;
        vis[i] = false;
    }
    for (int i = g.head[u]; i != -1; i = g.nxt[i])
    {
        Data t = g.to[i];
        dis[t.v] = t.w;
        pq.push(t);
    }
    int res = -1;
    while (!pq.empty())
    {
        Data t = pq.top();
        pq.pop();
        if (vis[t.v])
        {
            continue;
        }
        vis[t.v] = true;
        for (int i = g.head[t.v]; i != -1; i = g.nxt[i])
        {
            Data e = g.to[i];
            int a = t.w + e.w;
            if (dis[e.v] == -1 || dis[e.v] > a)
            {
                dis[e.v] = a;
                pq.push({e.v, a});
            }
        }
    }
}

int main()
{
    int n = 10;
    vector<vector<int>> edges = {{0, 1, 3}, {1, 3, 2}, {3, 1, 1}, {0, 2, 2}, {2, 0, 4}, {2, 3, 4}, {3, 2, 8}};
    int m = edges.size();
    CSRGraph g;
    g.init(n);
    for (int i = 0; i < m; i++)
    {
        int u = edges[i][0];
        int v = edges[i][1];
        int w = edges[i][2];
        g.addEdge(u, v, w);
    }
    dijkstra(g, 0, n);
    printf("dis[9]: %d\n", dis[9]); // dis[9]: -1
    printf("dis[3]: %d\n", dis[3]); // dis[3]: 5
    return 0;
}