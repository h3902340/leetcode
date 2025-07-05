#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Data {
    int v;
    int i;
};
struct Edge {
    int v;
    int start;
    int end;
};
const int N = 1e5;
vector<Edge> adj[N];
int dis[N];
bool vis[N];

class Solution {
   public:
    int minTime(int n, vector<vector<int>>& edges) {
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            dis[i] = -1;
            vis[i] = false;
        }
        for (auto& e : edges) {
            int u = e[0];
            int v = e[1];
            int start = e[2];
            int end = e[3];
            adj[u].push_back({v, start, end});
        }
        auto cmp = [&](Data a, Data b) { return a.v > b.v; };
        priority_queue<Data, vector<Data>, decltype(cmp)> pq(cmp);
        dis[0] = 0;
        pq.push({0, 0});
        while (!pq.empty()) {
            Data t = pq.top();
            pq.pop();
            if (vis[t.i]) {
                continue;
            }
            vis[t.i] = true;
            for (auto& e : adj[t.i]) {
                if (t.v > e.end) continue;
                int a = t.v;
                if (a < e.start) {
                    a = e.start;
                }
                a++;
                if (dis[e.v] == -1 || dis[e.v] > a) {
                    dis[e.v] = a;
                    pq.push({a, e.v});
                }
            }
        }
        return dis[n - 1];
    }
};

int main() {
    string problemName = "3604";
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
        auto res = sol.minTime(n, edges);
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