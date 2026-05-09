#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Edge
{
    int v;
    int w;
};
struct Data
{
    int v;
    int k;
};
const int N = 1e3;
vector<Edge> adj[N];
int vis[N];
Data q[N * 2];
class Solution
{
public:
    int minimumThreshold(int n, vector<vector<int>> &edges, int source, int target, int k)
    {
        if (source == target)
        {
            return 0;
        }
        int m = edges.size();
        int l = 0;
        int r = 0;
        for (int i = 0; i < n; i++)
        {
            adj[i].clear();
        }
        for (int i = 0; i < m; i++)
        {
            int u = edges[i][0];
            int v = edges[i][1];
            int w = edges[i][2];
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
            r = max(r, w);
        }
        int res = -1;
        while (l <= r)
        {
            int mid = (l + r) / 2;
            for (int i = 0; i < n; i++)
            {
                vis[i] = -1;
            }
            int a = 0;
            int b = 1;
            q[0] = {source, k};
            vis[source] = k;
            bool ok = false;
            while (a < b)
            {
                Data u = q[a++];
                for (auto &e : adj[u.v])
                {
                    int uk = u.k;
                    if (e.w > mid)
                    {
                        if (uk == 0)
                        {
                            continue;
                        }
                        uk--;
                    }
                    if (e.v == target)
                    {
                        ok = true;
                        break;
                    }
                    if (vis[e.v] >= uk)
                    {
                        continue;
                    }
                    vis[e.v] = uk;
                    q[b++] = {e.v, uk};
                }
                if (ok)
                {
                    break;
                }
            }
            if (ok)
            {
                r = mid - 1;
                res = mid;
            }
            else
            {
                l = mid + 1;
            }
        }
        return res;
    }
};

int main()
{
    string problemName = "3924";
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
        auto edges = jread_vector2d(line_in);
        getline(file_in, line_in);
        auto source = jread_int(line_in);
        getline(file_in, line_in);
        auto target = jread_int(line_in);
        getline(file_in, line_in);
        auto k = jread_int(line_in);
        auto res = sol.minimumThreshold(n, edges, source, target, k);
        getline(file_out, line_out);
        auto ans = jread_int(line_out);
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