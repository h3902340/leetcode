#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
const int MOD = 1e9 + 7;
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

class Solution {
   public:
    int sumOfNumbers(int l, int r, int k) {
        int x = l + r;
        int y = r - l + 1;
        return mul(mul(mul(x, mul(sub(pow(10, k), 1), inv(9))), pow(y, k)),
                   inv(2));
    }
};

int main() {
    string problemName = "3855";
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
        auto l = jread_int(line_in);
        getline(file_in, line_in);
        auto r = jread_int(line_in);
        getline(file_in, line_in);
        auto k = jread_int(line_in);
        auto res = sol.sumOfNumbers(l, r, k);
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