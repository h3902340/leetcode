#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

// TODO: try Tarjan's offline LCA
struct Neighbor {
    int v;
    int w;
};
const int NMAX = 1e5;
const int WALKMAX = NMAX * 2 - 1;
const int LOGWALKMAX = 18;
const int K = 3;
vector<Neighbor> adj[NMAX];
int depth[NMAX];
int s[NMAX];
int visitCount[NMAX];
int w[NMAX];
int walk[WALKMAX];
int walkIndex[NMAX];
int memo[WALKMAX][LOGWALKMAX];
class Solution {
   public:
    vector<int> minimumWeight(vector<vector<int>>& edges,
                              vector<vector<int>>& queries) {
        int n = edges.size() + 1;
        int m = queries.size();
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            visitCount[i] = 0;
        }
        for (auto e : edges) {
            adj[e[0]].push_back({e[1], e[2]});
            adj[e[1]].push_back({e[0], e[2]});
        }
        adj[0].push_back({0, 0});
        depth[0] = 0;
        w[0] = 0;
        int i = 0;
        s[0] = 0;
        int ws = 0;
        while (i >= 0) {
            int t = s[i];
            walk[ws] = t;
            walkIndex[t] = ws;
            ws++;
            visitCount[t]++;
            if (visitCount[t] == adj[t].size()) {
                i--;
                continue;
            }
            for (auto e : adj[t]) {
                if (visitCount[e.v] > 0) continue;
                s[++i] = e.v;
                depth[e.v] = depth[t] + 1;
                w[e.v] = w[t] + e.w;
                break;
            }
        }
        for (int i = 0; i < ws; i++) {
            memo[i][0] = walk[i];
        }
        int k = 1;
        for (int j = 1; k < ws; j++) {
            for (int i = 0; i + k * 2 - 1 < ws; i++) {
                int a = memo[i][j - 1];
                int b = memo[i + k][j - 1];
                memo[i][j] = depth[a] < depth[b] ? a : b;
            }
            k *= 2;
        }
        vector<int> ans(m);
        for (int i = 0; i < m; i++) {
            ans[i] = 0;
            for (int j = 0; j < K; j++) {
                ans[i] += w[queries[i][j]];
                for (int k = j + 1; k < K; k++) {
                    int p = lca(queries[i][j], queries[i][k]);
                    ans[i] -= w[p];
                }
            }
        }
        return ans;
    }

   private:
    int lca(int a, int b) {
        a = walkIndex[a];
        b = walkIndex[b];
        if (a > b) {
            swap(a, b);
        }
        int k = 1;
        int j = 0;
        while (a + k - 1 <= b) {
            k *= 2;
            j++;
        }
        j--;
        int mina = memo[a][j];
        k = 1;
        j = 0;
        while (a <= b - k + 1) {
            k *= 2;
            j++;
        }
        j--;
        k /= 2;
        int minb = memo[b - k + 1][j];
        return depth[mina] < depth[minb] ? mina : minb;
    }
};

int main() {
    string problemName = "3553";
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
        auto edges = jread_vector2d(line_in);
        getline(file_in, line_in);
        auto queries = jread_vector2d(line_in);
        auto res = sol.minimumWeight(edges, queries);
        getline(file_out, line_out);
        auto ans = jread_vector(line_out);
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