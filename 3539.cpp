#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int MOD = 1e9 + 7;
const int N = 50;
const int M = 30;
const int K = 30;
int fact[M + 1];
int ifact[M + 1];
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
    fact[0] = 1;
    ifact[0] = 1;
    for (int i = 1; i <= M; i++) {
        fact[i] = (long long)fact[i - 1] * i % MOD;
        ifact[i] = powMod(fact[i], MOD - 2, MOD);
    }
    isInit = true;
}

int memo[M + 1][K + 1][M * 2 + 1][N + 1];

class Solution {
   public:
    vector<int> _nums;
    int n;
    int magicalSum(int m, int k, vector<int>& nums) {
        init();
        n = nums.size();
        for (int i = 0; i <= m; i++) {
            for (int j = 0; j <= k; j++) {
                for (int x = 0; x <= m * 2; x++) {
                    for (int y = 0; y <= n; y++) {
                        memo[i][j][x][y] = -1;
                    }
                }
            }
        }
        _nums = nums;
        int res = (long long)fact[m] * dfs(m, k, 0, 0) % MOD;
        return res;
    }
    int dfs(int m, int k, int mask, int i) {
        if (memo[m][k][mask][i] != -1) {
            return memo[m][k][mask][i];
        }
        if (i == n) {
            if (m > 0) {
                memo[m][k][mask][i] = 0;
                return 0;
            }
            int oneCount = getOneCount(mask);
            if (k != oneCount) {
                memo[m][k][mask][i] = 0;
                return 0;
            }
            memo[m][k][mask][i] = 1;
            return 1;
        }
        if (m == 0) {
            int oneCount = getOneCount(mask);
            if (k != oneCount) {
                memo[m][k][mask][i] = 0;
                return 0;
            }
            memo[m][k][mask][i] = 1;
            return 1;
        }
        if (k == 0) {
            if (mask > 0) {
                memo[m][k][mask][i] = 0;
                return 0;
            }
            if (m > 0) {
                memo[m][k][mask][i] = 0;
                return 0;
            }
            memo[m][k][mask][i] = 1;
            return 1;
        }
        int res = 0;
        for (int j = 0; j <= m; j++) {
            int mNew = m - j;
            int maskNew = mask + j;
            int kNew = k - (maskNew & 1);
            int temp = (long long)ifact[j] * powMod(_nums[i], j, MOD) % MOD;
            temp = (long long)temp * dfs(mNew, kNew, maskNew >> 1, i + 1) % MOD;
            res += temp;
            if (res >= MOD) {
                res -= MOD;
            }
        }
        memo[m][k][mask][i] = res;
        return res;
    }
    int getOneCount(int a) {
        int res = 0;
        while (a > 0) {
            if (a & 1) {
                res++;
            }
            a >>= 1;
        }
        return res;
    }
};

int main() {
    string problemName = "3539";
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
        auto m = jread_int(line_in);
        getline(file_in, line_in);
        auto k = jread_int(line_in);
        getline(file_in, line_in);
        auto nums = jread_vector(line_in);
        auto res = sol.magicalSum(m, k, nums);
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