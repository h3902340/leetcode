#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 1e5;
const int M = N - 1;
int to[M << 1];
int nxt[M << 1];
int head[N];
int eCnt;
void addEdge(int u, int v) {
    to[eCnt] = v;
    nxt[eCnt] = head[u];
    head[u] = eCnt++;
}
void init(int n) {
    eCnt = 0;
    for (int i = 0; i < n; i++) {
        head[i] = -1;
    }
}
int par[N];
int q[N];

class Solution {
   public:
    vector<int> smallestThreeColorTree(int n, vector<vector<int>>& edges) {
        int m = edges.size();
        init(n);
        for (int i = 0; i < m; i++) {
            int u = edges[i][0];
            int v = edges[i][1];
            addEdge(u, v);
            addEdge(v, u);
        }
        vector<int> res(n, -1);
        for (int i = 0; i < n; i++) {
            bool ok = true;
            for (int j = head[i]; j != -1; j = nxt[j]) {
                int v = to[j];
                if (res[v] == 0) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                res[i] = 0;
            }
        }
        for (int i = 0; i < n; i++) {
            if (res[i] != -1) {
                continue;
            }
            par[i] = -1;
            q[0] = i;
            res[i] = 1;
            int l = 0;
            int r = 1;
            while (l < r) {
                int u = q[l++];
                int c = res[u] ^ 3;
                for (int j = head[u]; j != -1; j = nxt[j]) {
                    int v = to[j];
                    if (par[u] == v) {
                        continue;
                    }
                    if (res[v] == 0) {
                        continue;
                    }
                    par[v] = u;
                    q[r++] = v;
                    res[v] = c;
                }
            }
        }
        return res;
    }
};

int main() {
    string problemName = "SmallestThreeColorTree";
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
        auto res = sol.smallestThreeColorTree(n, edges);
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