#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 1e5;
int parent[N];
int sz[N];
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
        parent[b] = a;
        sz[a] += sz[b];
        sz[b] = 0;
    }
}
void init(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = -1;
        sz[i] = 1;
    }
}
class Solution {
   public:
    int maxActivated(vector<vector<int>>& points) {
        int n = points.size();
        init(n);
        unordered_map<int, int> x;
        unordered_map<int, int> y;
        for (int i = 0; i < n; i++) {
            if (x.count(points[i][0])) {
                unite(x[points[i][0]], i);
            } else {
                x[points[i][0]] = i;
            }
            if (y.count(points[i][1])) {
                unite(y[points[i][1]], i);
            } else {
                y[points[i][1]] = i;
            }
        }
        int mx1 = 0;
        int mx2 = 0;
        for (int i = 0; i < n; i++) {
            if (mx1 < sz[i]) {
                mx2 = mx1;
                mx1 = sz[i];
            } else if (mx2 < sz[i]) {
                mx2 = sz[i];
            }
        }
        return mx1 + mx2 + 1;
    }
};

int main() {
    string problemName = "3873";
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
        auto points = jread_vector2d(line_in);
        auto res = sol.maxActivated(points);
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