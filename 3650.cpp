#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
const int N = 5e4;
const int M = 1e5;
ll to[M << 1];
int nxt[M << 1];
int head[N];
int eCnt;
int dis[N];
bool vis[N];
void addEdge(int u, int v, int w) {
    to[eCnt] = (ll)w << 32 | v;
    nxt[eCnt] = head[u];
    head[u] = eCnt++;
}
void init(int n) {
    eCnt = 0;
    for (int i = 0; i < n; i++) {
        head[i] = -1;
        dis[i] = INT32_MAX;
        vis[i] = false;
    }
}

class Solution {
   public:
    int minCost(int n, vector<vector<int>>& edges) {
        priority_queue<ll, vector<ll>, greater<ll>> pq;
        init(n);
        for (auto& e : edges) {
            int u = e[0];
            int v = e[1];
            int w = e[2];
            addEdge(u, v, w);
            addEdge(v, u, w << 1);
        }
        for (int i = head[0]; i != -1; i = nxt[i]) {
            ll e = to[i];
            int v = e;
            int w = e >> 32;
            dis[v] = w;
            pq.push(e);
        }
        int res = -1;
        while (!pq.empty()) {
            ll t = pq.top();
            int v = t;
            int w = t >> 32;
            pq.pop();
            if (vis[v]) {
                continue;
            }
            vis[v] = true;
            if (v == n - 1) {
                res = w;
                break;
            }
            for (int i = head[v]; i != -1; i = nxt[i]) {
                ll e = to[i];
                int ev = e;
                int ew = e >> 32;
                int a = w + ew;
                if (dis[ev] > a) {
                    dis[ev] = a;
                    pq.push((ll)a << 32 | ev);
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