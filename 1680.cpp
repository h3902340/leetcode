#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
#define lg2(x) (32 - __builtin_clz(x))
const int N = 1e5;
const int U = lg2(N);
const int MOD = 1e9 + 7;
int dp[U];
bool isInit = false;
int mul(int a, int b) { return (ll)a * b % MOD; }
int pow(int a, int b) {
    if (a == 0) return 0;
    if (a == 1) return 1;
    if (b == 0) return 1;
    if (b & 1) {
        int temp = pow(a, b - 1);
        return mul(a, temp);
    }
    int temp = pow(a, b >> 1);
    return mul(temp, temp);
}
int inv(int a) { return pow(a, MOD - 2); }
int sub(int a, int b) {
    a -= b;
    if (a < 0) {
        a += MOD;
    }
    return a;
}
int add(int a, int b) {
    a += b;
    if (a >= MOD) {
        a -= MOD;
    }
    return a;
}
int calc(int r, int x, int y) {
    return add(mul(inv(r - 1), sub(mul(x - y, pow(r, y + 1)), x)),
               mul(inv(mul(r - 1, r - 1)), sub(pow(r, y + 1), r)));
}
void init() {
    int r = 2;
    int x = r - 1;
    int y = (r >> 1) - 1;
    dp[1] = 1;
    for (int i = 2; i < U; i++) {
        y = r - 1;
        r <<= 1;
        x = r - 1;
        dp[i] = add(mul(dp[i - 1], pow(2, mul(i, y + 1))), calc(r, x, y));
    }
}

class Solution {
   public:
    int concatenatedBinary(int n) {
        if (!isInit) {
            init();
            isInit = true;
        }
        int b = lg2(n);
        int r = pow(2, b);
        int x = n;
        int y = n - (r >> 1);
        return add(mul(dp[b - 1], pow(2, mul(b, y + 1))), calc(r, x, y));
    }
};

int main() {
    string problemName = "1680";
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
        auto res = sol.concatenatedBinary(n);
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