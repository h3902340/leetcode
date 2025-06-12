#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int NMAX = 1e5;
vector<int> adj1[NMAX];
vector<int> adj2[NMAX];
int q[NMAX];
int parent[NMAX];
int depth[NMAX];
int tmp[2];

class Solution {
   public:
    vector<int> maxTargetNodes(vector<vector<int>>& edges1,
                               vector<vector<int>>& edges2) {
        int n = edges1.size() + 1;
        int m = edges2.size() + 1;
        for (int i = 0; i < n; i++) {
            adj1[i].clear();
        }
        for (int i = 0; i < m; i++) {
            adj2[i].clear();
        }
        for (auto e : edges1) {
            adj1[e[0]].push_back(e[1]);
            adj1[e[1]].push_back(e[0]);
        }
        for (auto e : edges2) {
            adj2[e[0]].push_back(e[1]);
            adj2[e[1]].push_back(e[0]);
        }
        int max = calcTarget(adj2, m);
        if (max < m - max) {
            max = m - max;
        }
        vector<int> res(n);
        tmp[0] = calcTarget(adj1, n);
        tmp[1] = n - tmp[0];
        for (int i = 0; i < n; i++) {
            res[i] = tmp[depth[i] & 1] + max;
        }
        return res;
    }

   private:
    int calcTarget(vector<int> adj[NMAX], int n) {
        int l = 0;
        int r = 0;
        q[r++] = 0;
        parent[0] = -1;
        depth[0] = 0;
        int res = 0;
        while (l < r) {
            int f = q[l++];
            if ((depth[f] & 1) == 0) {
                res++;
            }
            for (auto& e : adj[f]) {
                if (e == parent[f]) continue;
                q[r++] = e;
                parent[e] = f;
                depth[e] = depth[f] + 1;
            }
        }
        return res;
    }
};

int main() {
    string problemName = "3373";
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
        auto edges1 = jread_vector2d(line_in);
        getline(file_in, line_in);
        auto edges2 = jread_vector2d(line_in);
        auto res = sol.maxTargetNodes(edges1, edges2);
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