#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
struct Res {
    ll v;
    int cnt;
};
const int N = 1e5;
vector<int> adj[N];
int parent[N];

class Solution {
   public:
    int minIncrease(int n, vector<vector<int>>& edges, vector<int>& cost) {
        for (int i = 0; i < n; i++) {
            adj[i].clear();
        }
        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }
        parent[0] = -1;
        return bfs(0, cost).cnt;
    }
    Res bfs(int i, vector<int>& cost) {
        ll max = 0;
        int maxCnt = 0;
        int totalChange = adj[i].size();
        if (i != 0) {
            totalChange--;
        }
        for (auto e : adj[i]) {
            if (parent[i] == e) continue;
            parent[e] = i;
            Res a = bfs(e, cost);
            if (max < a.v) {
                max = a.v;
                maxCnt = 1;
            } else if (max == a.v) {
                maxCnt++;
            }
            totalChange += a.cnt;
        }
        totalChange -= maxCnt;
        ll maxCost = max + cost[i];
        return {maxCost, totalChange};
    }
};

int main() {
    string problemName = "3593";
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
        getline(file_in, line_in);
        auto cost = jread_vector(line_in);
        auto res = sol.minIncrease(n, edges, cost);
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