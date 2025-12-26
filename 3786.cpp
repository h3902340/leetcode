#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
const int N = 1e5;
const int M = N - 1;
const int G = 20;
int p[N];
int q[N];
int total[G];
int cnt[N];
// CSR Graph
int to[M << 1];
int nxt[M << 1];
int head[N];
int eCnt;
void addEdge(int u, int v) {
    to[eCnt] = v;
    nxt[eCnt] = head[u];
    head[u] = eCnt++;
}

class Solution {
public:
    long long interactionCosts(int n, vector<vector<int>>& edges,
                               vector<int>& group) {
        int m = edges.size();
        for (int i = 0; i < G; i++) {
            total[i] = 0;
        }
        for (int i = 0; i < n; i++) {
            head[i] = -1;
            group[i]--;
            total[group[i]]++;
        }
        eCnt = 0;
        for (int i = 0; i < m; i++) {
            int u = edges[i][0];
            int v = edges[i][1];
            addEdge(u, v);
            addEdge(v, u);
        }
        q[0] = 0;
        p[0] = -1;
        int f = 0;
        int b = 1;
        while (f < b) {
            int t = q[f++];
            for (int i = head[t]; i != -1; i = nxt[i]) {
                int c = to[i];
                if (c == p[t]) {
                    continue;
                }
                q[b++] = c;
                p[c] = t;
            }
        }
        ll res = 0;
        for (int j = 0; j < G; j++) {
            if (total[j] < 2) {
                continue;
            }
            for (int i = n - 1; i >= 1; i--) {
                int a = q[i];
                cnt[a] = 0;
                if (j == group[a]) {
                    cnt[a] = 1;
                }
                for (int i = head[a]; i != -1; i = nxt[i]) {
                    int c = to[i];
                    if (c == p[a]) {
                        continue;
                    }
                    cnt[a] += cnt[c];
                }
                if (cnt[a] > 0) {
                    res += (ll)cnt[a] * (total[j] - cnt[a]);
                }
            }
        }
        return res;
    }
};

int main() {
    string problemName = "3786";
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
        auto group = jread_vector(line_in);
        auto res = sol.interactionCosts(n, edges, group);
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