#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 13;
class DSU {
    int parent[N];
    int sz[N];

   public:
    void init(int n) {
        for (int i = 0; i < n; i++) {
            parent[i] = -1;
            sz[i] = 1;
        }
    }
    int find(int u) {
        int p = u;
        while (parent[p] != -1) {
            p = parent[p];
        }
        while (parent[u] != -1) {
            int tmp = parent[u];
            parent[u] = p;
            u = tmp;
        }
        return p;
    }
    void unite(int u, int v) {
        int a = find(u);
        int b = find(v);
        if (b != a) {
            if (sz[b] < sz[a]) {
                parent[b] = a;
                sz[a] += sz[b];
            } else {
                parent[a] = b;
                sz[b] += sz[a];
            }
        }
    }
};
DSU dsu;
bool adj[N][N];

class Solution {
   public:
    int evenSumSubgraphs(vector<int>& nums, vector<vector<int>>& edges) {
        int n = nums.size();
        int m = edges.size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                adj[i][j] = 0;
            }
        }
        for (int i = 0; i < m; i++) {
            int u = edges[i][0];
            int v = edges[i][1];
            adj[u][v] = 1;
            adj[v][u] = 1;
        }
        int cap = 1 << n;
        int res = 0;
        for (int i = 1; i < cap; i++) {
            bool ok = true;
            dsu.init(n);
            int score = 0;
            for (int j = 0; j < n; j++) {
                if ((i & (1 << j)) == 0) {
                    continue;
                }
                score += nums[j];
                for (int k = j + 1; k < n; k++) {
                    if ((i & (1 << k)) == 0) {
                        continue;
                    }
                    if (adj[j][k]) {
                        dsu.unite(j, k);
                    }
                }
            }
            int p = -1;
            for (int j = 0; j < n; j++) {
                if ((i & (1 << j)) == 0) {
                    continue;
                }
                int a = dsu.find(j);
                if (p != -1 && p != a) {
                    ok = false;
                    break;
                }
                p = a;
            }
            if (ok && (score % 2 == 0)) {
                res++;
            }
        }
        return res;
    }
};

int main() {
    string problemName = "3910";
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
        auto nums = jread_vector(line_in);
        getline(file_in, line_in);
        auto edges = jread_vector2d(line_in);
        auto res = sol.evenSumSubgraphs(nums, edges);
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