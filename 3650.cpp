#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Data {
    int v;
    int w;
};
const int N = 5e4;
vector<Data> adj[N];
int dis[N];
bool vis[N];
auto cmp = [](Data& a, Data& b) { return a.w > b.w; };

class Solution {
   public:
    int minCost(int n, vector<vector<int>>& edges) {
        priority_queue<Data, vector<Data>, decltype(cmp)> pq(cmp);
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            dis[i] = -1;
            vis[i] = false;
        }
        for (auto& e : edges) {
            int u = e[0];
            int v = e[1];
            int w = e[2];
            adj[u].push_back({v, w});
            adj[v].push_back({u, w << 1});
        }
        for (auto& e : adj[0]) {
            dis[e.v] = e.w;
            pq.push(e);
        }
        int res = -1;
        while (!pq.empty()) {
            Data t = pq.top();
            pq.pop();
            if (vis[t.v]) {
                continue;
            }
            vis[t.v] = true;
            if (t.v == n - 1) {
                res = t.w;
                break;
            }
            for (auto& e : adj[t.v]) {
                int a = t.w + e.w;
                if (dis[e.v] == -1 || dis[e.v] > a) {
                    dis[e.v] = a;
                    pq.push({e.v, a});
                }
            }
        }
        return res;
    }
};

int main() {
    string problemName = "3650";
    auto begin = jtimer();
    Solution sol;
    ifstream file_in("testcases/" + problemName + "_in.txt");
    ifstream file_out("testcases/" + problemName + "_out.txt");
    bool allPass = true;
    int caseCount = 0;
    int passCount = 0;
    string line_in;
    string line_out;
    while (getline(file_in, line_in)) {
        auto n = jread_int(line_in);
        getline(file_in, line_in);
        auto edges = jread_vector2d(line_in);
        auto res = sol.minCost(n, edges);
        getline(file_out, line_out);
        auto ans = jread_int(line_out);
        printf("Case %d", ++caseCount);
        if (res == ans) {
            passCount++;
            printf(" %s(PASS)", KGRN);
        } else {
            printf(" %s(WRONG)", KRED);
            allPass = false;
        }
        printf("\n%s", KNRM);
        jprint(res, "res");
        jprint(ans, "ans");
        printf("\n");
    }
    if (allPass) {
        printf("%sALL CORRECT [%d/%d]\n%s", KGRN, passCount, caseCount, KNRM);
    } else {
        printf("%sWRONG ANSWER [%d/%d]\n%s", KRED, passCount, caseCount, KNRM);
    }
    auto end = jtimer();
    jprint_time(begin, end);
    return 0;
}