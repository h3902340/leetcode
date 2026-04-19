#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
int arr[16];
int grid[4][4];
bool isPath[16];
ll memo[16][10][2];
class Solution {
   public:
    ll countGoodIntegersOnPath(ll l, ll r, string directions) {
        return f(r, directions) - f(l - 1, directions);
    }
    ll f(ll r, string& directions) {
        int d = 15;
        while (r > 0) {
            arr[d--] = r % 10;
            r /= 10;
        }
        for (; d >= 0; d--) {
            arr[d] = 0;
        }
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                grid[i][j] = arr[15 - i * 4 - j];
            }
        }
        for (int i = 1; i < 16; i++) {
            isPath[i] = false;
        }
        isPath[0] = true;
        int x = 0;
        int y = 0;
        for (int i = 0; i < 6; i++) {
            if (directions[i] == 'R') {
                isPath[x * 4 + (++y)] = true;
            } else {
                isPath[(++x) * 4 + y] = true;
            }
        }
        memset(memo, -1, sizeof(memo));
        return g(0, 0, 0);
    }
    ll g(int i, int pre, bool free) {
        if (i == 16) {
            return 1;
        }
        if (memo[i][pre][free] != -1) {
            return memo[i][pre][free];
        }
        ll res = 0;
        int hi = free ? 9 : arr[i];
        int lo = isPath[i] ? pre : 0;
        for (int j = lo; j < hi; j++) {
            if (isPath[i]) {
                res += g(i + 1, j, true);
            } else {
                res += g(i + 1, pre, true);
            }
        }
        if (lo <= hi) {
            if (isPath[i]) {
                res += g(i + 1, hi, free);
            } else {
                res += g(i + 1, pre, free);
            }
        }
        memo[i][pre][free] = res;
        return res;
    }
};

int main() {
    string problemName = "3906";
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
        auto l = jread_longlong(line_in);
        getline(file_in, line_in);
        auto r = jread_longlong(line_in);
        getline(file_in, line_in);
        auto directions = jread_string(line_in);
        auto res = sol.countGoodIntegersOnPath(l, r, directions);
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