#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 100;
int parent[N];
int find(int u) {
    int p = u;
    while (parent[p] >= 0) {
        p = parent[p];
    }
    while (parent[u] >= 0) {
        int tmp = parent[u];
        parent[u] = p;
        u = tmp;
    }
    return p;
}
void unite(int u, int v) {
    int a = find(u);
    int b = find(v);
    parent[a] += parent[b];
    parent[b] = a;
}
void init(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = -1;
    }
}

class Solution {
   public:
    int maximizeSquareHoleArea(int n, int m, vector<int>& hBars,
                               vector<int>& vBars) {
        int x = hBars.size();
        int y = vBars.size();
        int mxa = f(hBars, x);
        int mxb = f(vBars, y);
        int res = min(mxa, mxb) + 1;
        res *= res;
        return res;
    }
    int f(vector<int>& bars, int x) {
        unordered_map<int, int> mp;
        init(x);
        int mx = 1;
        for (int i = 0; i < x; i++) {
            mp[bars[i]] = i;
            if (mp.count(bars[i] - 1)) {
                unite(i, mp[bars[i] - 1]);
            }
            if (mp.count(bars[i] + 1)) {
                unite(i, mp[bars[i] + 1]);
            }
            int a = -parent[i];
            if (mx < a) {
                mx = a;
            }
        }
        return mx;
    }
};

int main() {
    string problemName = "2943";
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
        auto m = jread_int(line_in);
        getline(file_in, line_in);
        auto hBars = jread_vector(line_in);
        getline(file_in, line_in);
        auto vBars = jread_vector(line_in);
        auto res = sol.maximizeSquareHoleArea(n, m, hBars, vBars);
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