#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
const int MOD = 1e9 + 7;
const int N = 1e5;
int fac[N + 1];
int ifac[N + 1];
bool isInit = false;
int powMod(int a, int b, int m) {
    if (a == 0) return 0;
    if (a == 1) return a % m;
    if (b == 0) return 1;
    if (b & 1) {
        long temp = powMod(a, b - 1, m);
        return (a * temp) % m;
    }
    long temp = powMod(a, b >> 1, m);
    return (temp * temp) % m;
}
static void init() {
    if (isInit) return;
    fac[0] = 1;
    for (int i = 1; i <= N; i++) {
        fac[i] = (ll)fac[i - 1] * i % MOD;
    }
    ifac[N] = powMod(fac[N], MOD - 2, MOD);
    for (int i = N; i >= 1; i--) {
        ifac[i - 1] = (ll)ifac[i] * i % MOD;
    }
    isInit = true;
}

class Solution {
   public:
    int countGoodArrays(int n, int m, int k) {
        init();
        int a = m;
        if (n - k - 1 > 0) {
            a = mul(a, powMod(m - 1, n - k - 1, MOD));
        }
        int b = mul(fac[n - 1], mul(ifac[k], ifac[n - 1 - k]));
        return mul(a, b);
    }
    int mul(int a, int b) { return (ll)a * b % MOD; }
};

int main() {
    string problemName = "3405";
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
        auto k = jread_int(line_in);
        auto res = sol.countGoodArrays(n, m, k);
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