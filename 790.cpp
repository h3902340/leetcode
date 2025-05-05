#include <_printf.h>

const int MOD = 1000000007;
const int NMAX = 1001;
int dp[NMAX];

bool isInit = false;
static void init() {
    if (isInit) return;
    dp[0] = 1;
    dp[1] = 1;
    dp[2] = 2;
    for (int i = 3; i < NMAX; i++) {
        dp[i] = ((dp[i - 1] * 2) % MOD + dp[i - 3]) % MOD;
    }
    isInit = true;
}

class Solution {
   public:
    int numTilings(int n) {
        init();
        return dp[n];
    }
};

// 5
int n = 3;

int main() {
    Solution sol;
    int ans = sol.numTilings(n);
    printf("ans = %d\n", ans);
    return 0;
}