#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int MOD = 1e9 + 7;
const int N = 300;
const int X = 5;
int dp[N + 1][X + 1];
bool isInit = false;
int add(int a, int b) {
    a += b;
    if (a >= MOD) {
        a -= MOD;
    }
    return a;
}
int _pow(int a, int b, int v) {
    if (a == 0) return 0;
    if (a == 1) return v;
    if (b == 0) return v;
    if (b & 1) {
        return _pow(a, b - 1, v * a);
    }
    return _pow(a * a, b >> 1, v);
}
int pow(int a, int b) { return _pow(a, b, 1); }
static void init() {
    for (int j = 1; j <= X; j++) {
        dp[0][j] = 1;
        for (int i = 1; i <= N; i++) {
            dp[i][j] = 0;
        }
        for (int k = 1; k <= N; k++) {
            int a = pow(k, j);
            if (a > N) {
                break;
            }
            for (int i = N; i >= a; i--) {
                dp[i][j] = add(dp[i][j], dp[i - a][j]);
            }
        }
    }
    isInit = true;
}

class Solution {
   public:
    int numberOfWays(int n, int x) {
        if (!isInit) {
            init();
        }
        return dp[n][x];
    }
};

int main() {
    string problemName = "2787";
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
        auto x = jread_int(line_in);
        auto res = sol.numberOfWays(n, x);
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