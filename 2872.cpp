#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 3e4;
vector<int> adj[N];
int st[N];
int vis[N];

class Solution {
   public:
    int maxKDivisibleComponents(int n, vector<vector<int>>& edges,
                                vector<int>& values, int k) {
        int m = edges.size();
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            vis[i] = 0;
        }
        for (int i = 0; i < m; i++) {
            int u = edges[i][0];
            int v = edges[i][1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        st[0] = 0;
        vis[0] = 1;
        int i = 0;
        int j = 1;
        while (i < j) {
            int t = st[i++];
            for (auto& c : adj[t]) {
                if (vis[c]) {
                    c = -1;
                    continue;
                }
                st[j++] = c;
                vis[c] = 1;
            }
        }
        int res = 0;
        for (int l = j - 1; l >= 0; l--) {
            int a = st[l];
            long long sum = values[a];
            for (auto& c : adj[a]) {
                if (c == -1) {
                    continue;
                }
                sum += vis[c];
            }
            sum %= k;
            vis[a] = sum;
            if (sum == 0) {
                res++;
            }
        }
        return res;
    }
};

int main() {
    string problemName = "2872";
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
        auto values = jread_vector(line_in);
        getline(file_in, line_in);
        auto k = jread_int(line_in);
        auto res = sol.maxKDivisibleComponents(n, edges, values, k);
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