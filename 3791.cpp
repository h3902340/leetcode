#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
const int D = 8;
ll dp[D + 1][D * 9 + 1];
int digit[D << 1];
bool isInit = false;
void init() {
    for (int i = 0; i <= D; i++) {
        for (int j = 0; j <= D * 9; j++) {
            dp[i][j] = 0;
        }
    }
    dp[0][0] = 1;
    for (int i = 1; i <= D; i++) {
        for (int j = 0; j <= i * 9; j++) {
            for (int k = 0; k <= 9; k++) {
                if (k > j) {
                    break;
                }
                dp[i][j] += dp[i - 1][j - k];
            }
        }
    }
}
class Solution {
   public:
    long long countBalanced(long long low, long long high) {
        if (!isInit) {
            init();
            isInit = true;
        }
        return f(high) - f(low - 1);
    }
    ll f(ll n) {
        if (n == 0) {
            return 1;
        }
        int d = 0;
        while (n > 0) {
            int r = n % 10;
            digit[d++] = r;
            n /= 10;
        }
        d--;
        ll res = 0;
        int x = 0;
        int y = 0;
        for (int j = d; j >= 0; j--) {
            int h = j >> 1;
            int s = h * 9;
            for (int i = 0; i < digit[j]; i++) {
                for (int k = max(0, y - x - i); k <= s; k++) {
                    int a = k + x + i;
                    if (j & 1) {
                        res += dp[h][k] * dp[h + 1][a - y];
                    } else {
                        res += dp[h][k] * dp[h][a - y];
                    }
                }
            }
            x += digit[j];
            swap(x, y);
        }
        if (x == y) {
            res++;
        }
        return res;
    }
};

int main() {
    string problemName = "3791";
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
        auto low = jread_longlong(line_in);
        getline(file_in, line_in);
        auto high = jread_longlong(line_in);
        auto res = sol.countBalanced(low, high);
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