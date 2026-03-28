#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
const int N = 1e5;
const int MOD = 1e9 + 7;
int f[N];
int finv[N];
bool isInit = false;
int add(int a, int b) { return (a + b) % MOD; }
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
int C(int a, int b) {
    int res = mul(f[a], finv[b]);
    res = mul(res, finv[a - b]);
    return res;
}
void init() {
    f[0] = 1;
    finv[0] = 1;
    for (int i = 1; i < N; i++) {
        f[i] = mul(i, f[i - 1]);
        finv[i] = inv(f[i]);
    }
}
class Solution {
   public:
    int countVisiblePeople(int n, int pos, int k) {
        if (!isInit) {
            init();
            isInit = true;
        }
        int res = C(n - 1, k);
        res = add(res, res);
        return res;
    }
};

int main() {
    string problemName = "3881";
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
        auto pos = jread_int(line_in);
        getline(file_in, line_in);
        auto k = jread_int(line_in);
        auto res = sol.countVisiblePeople(n, pos, k);
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