#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 1e5;
int parent[N];

class Solution {
   public:
    int minTime(int n, vector<vector<int>> &edges, int k) {
        for (int i = 0; i < n; i++) {
            parent[i] = -1;
        }
        auto cmp = [](vector<int> &a, vector<int> &b) { return a[2] < b[2]; };
        sort(edges.begin(), edges.end(), cmp);
        int cnt = n;
        int m = edges.size();
        int i = m - 1;
        for (; i >= 0; i--) {
            int u = edges[i][0];
            int v = edges[i][1];
            int a = find(u);
            int b = find(v);
            if (a != b) {
                unite(a, b);
                cnt--;
                if (cnt < k) {
                    break;
                }
            }
        }
        if (i == -1) {
            return 0;
        }
        return edges[i][2];
    }
    // DSU
    void unite(int u, int v) {
        int a = find(u);
        int b = find(v);
        if (b != a) {
            parent[b] = a;
        }
    }
    int find(int u) {
        int p = u;
        while (parent[p] != -1) {
            p = parent[p];
        }
        // collapsing
        while (parent[u] != -1) {
            int tmp = parent[u];
            parent[u] = p;
            u = tmp;
        }
        return p;
    }
};

int main() {
    string problemName = "3608";
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
        auto k = jread_int(line_in);
        auto res = sol.minTime(n, edges, k);
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