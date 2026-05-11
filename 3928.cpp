#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
struct Data
{
    int v;
    ll w;
};

// CSR Graph
const int N = 1000;
const int M = 2000;
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
    void addEdge(int u, int v, ll w)
    {
        to[eCnt] = {v, w};
        nxt[eCnt] = head[u];
        head[u] = eCnt++;
    }
};

// Dijkstra
ll dis[N];
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
            ll a = t.w + e.w;
            if (dis[e.v] == -1 || dis[e.v] > a)
            {
                dis[e.v] = a;
                pq.push({e.v, a});
            }
        }
    }
}
ll cost[N][N];
CSRGraph g1;
CSRGraph g2;
class Solution
{
public:
    vector<int> minCost(int n, vector<int> &prices,
                        vector<vector<int>> &roads)
    {
        g1.init(n);
        g2.init(n);
        for (auto &r : roads)
        {
            int u = r[0];
            int v = r[1];
            int cost = r[2];
            int tax = r[3];
            ll prod = (ll)cost * tax;
            g1.addEdge(u, v, cost);
            g1.addEdge(v, u, cost);
            g2.addEdge(u, v, prod);
            g2.addEdge(v, u, prod);
        }
        vector<int> res(n);
        for (int i = 0; i < n; i++)
        {
            dijkstra(g1, i, n);
            cost[i][i] = prices[i];
            for (int j = 0; j < n; j++)
            {
                if (i == j)
                {
                    continue;
                }
                if (dis[j] == -1)
                {
                    cost[i][j] = -1;
                }
                else
                {
                    cost[i][j] = dis[j] + prices[j];
                }
            }
            dijkstra(g2, i, n);
            int a = prices[i];
            for (int j = 0; j < n; j++)
            {
                if (i == j)
                {
                    continue;
                }
                if (dis[j] != -1)
                {
                    cost[i][j] += dis[j];
                    if (a > cost[i][j])
                    {
                        a = cost[i][j];
                    }
                }
            }
            res[i] = a;
        }
        return res;
    }
};

int main()
{
    string problemName = "3928";
    auto begin = jtimer();
    Solution sol;
    ifstream file_in("testcases/" + problemName + "_in.txt");
    ifstream file_out("testcases/" + problemName + "_out.txt");
    bool allPass = true;
    int caseCount = 0;
    int passCount = 0;
    string line_in;
    string line_out;
    while (getline(file_in, line_in))
    {
        auto n = jread_int(line_in);
        getline(file_in, line_in);
        auto prices = jread_vector(line_in);
        getline(file_in, line_in);
        auto roads = jread_vector2d(line_in);
        auto res = sol.minCost(n, prices, roads);
        getline(file_out, line_out);
        auto ans = jread_vector(line_out);
        printf("Case %d", ++caseCount);
        if (res == ans)
        {
            passCount++;
            printf(" %s(PASS)", KGRN);
        }
        else
        {
            printf(" %s(WRONG)", KRED);
            allPass = false;
        }
        printf("\n%s", KNRM);
        jprint(res, "res");
        jprint(ans, "ans");
        printf("\n");
    }
    if (allPass)
    {
        printf("%sALL CORRECT [%d/%d]\n%s", KGRN, passCount, caseCount, KNRM);
    }
    else
    {
        printf("%sWRONG ANSWER [%d/%d]\n%s", KRED, passCount, caseCount, KNRM);
    }
    auto end = jtimer();
    jprint_time(begin, end);
    return 0;
}