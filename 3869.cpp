#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
const int N = 16;
int d[N];
int sz;
bool good[136];
bool isInit = false;
ll memo[N][10][4][136];
void init() {
    memset(memo, -1, sizeof(memo));
    for (int i = 0; i < 10; i++) {
        good[i] = true;
    }
    for (int i = 1; i < 10; i++) {
        for (int j = i + 1; j < 10; j++) {
            good[i * 10 + j] = true;
        }
        for (int j = i - 1; j >= 0; j--) {
            good[i * 10 + j] = true;
        }
    }
    for (int i = 3; i < 10; i++) {
        good[120 + i] = true;
    }
    for (int i = 4; i < 6; i++) {
        good[130 + i] = true;
    }
}
class Solution {
   public:
    long long countFancy(long long l, long long r) {
        if (!isInit) {
            init();
            isInit = true;
        }
        return f(r) - f(l - 1);
    }
    ll f(ll r) {
        if (r < 10) {
            return r + 1;
        }
        sz = 0;
        while (r > 0) {
            d[sz++] = r % 10;
            r /= 10;
        }
        ll res = 0;
        int i = sz - 1;
        for (int j = 0; j <= d[i]; j++) {
            bool free = j < d[i];
            res += dfs(i - 1, j, 0, j, free);
        }
        return res;
    }
    ll dfs(int i, int pre, int dir, int s, bool free) {
        if (free && memo[i][pre][dir][s] != -1) {
            return memo[i][pre][dir][s];
        }
        int cap = free ? 9 : d[i];
        if (i == 0) {
            ll res = 0;
            for (int j = 0; j <= cap; j++) {
                if (dir == 0) {
                    if (j != pre) {
                        res++;
                        continue;
                    }
                } else if (dir == 1) {
                    if (j > pre) {
                        res++;
                        continue;
                    }
                } else if (dir == 2) {
                    if (j < pre) {
                        res++;
                        continue;
                    }
                }
                if (good[s + j]) {
                    res++;
                }
            }
            if (free) {
                memo[i][pre][dir][s] = res;
            }
            return res;
        }
        ll res = 0;
        if (dir == 0) {
            if (pre == 0) {
                for (int j = 0; j <= cap; j++) {
                    res += dfs(i - 1, j, 0, s + j, free || j < d[i]);
                }
            } else {
                int cap2 = min(pre - 1, cap);
                for (int j = 0; j <= cap; j++) {
                    if (j >= pre + 1 && j <= cap) {
                        res += dfs(i - 1, j, 1, s + j, free || j < d[i]);
                    } else if (j <= cap2) {
                        res += dfs(i - 1, j, 2, s + j, free || j < d[i]);
                    } else {
                        res += dfs(i - 1, j, 3, s + j, free || j < d[i]);
                    }
                }
            }
        } else if (dir == 1) {
            int cap2 = min(pre, cap);
            for (int j = 0; j <= cap2; j++) {
                res += dfs(i - 1, j, 3, s + j, free || j < d[i]);
            }
            for (int j = pre + 1; j <= cap; j++) {
                res += dfs(i - 1, j, 1, s + j, free || j < d[i]);
            }
        } else if (dir == 2) {
            int cap2 = min(pre - 1, cap);
            for (int j = 0; j <= cap2; j++) {
                res += dfs(i - 1, j, 2, s + j, free || j < d[i]);
            }
            for (int j = cap2 + 1; j <= cap; j++) {
                res += dfs(i - 1, j, 3, s + j, free || j < d[i]);
            }
        } else {
            for (int j = 0; j <= cap; j++) {
                res += dfs(i - 1, j, 3, s + j, free || j < d[i]);
            }
        }
        if (free) {
            memo[i][pre][dir][s] = res;
        }
        return res;
    }
};

int main() {
    string problemName = "3869";
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
        auto res = sol.countFancy(l, r);
        getline(file_out, line_out);
        auto ans = jread_longlong(line_out);
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