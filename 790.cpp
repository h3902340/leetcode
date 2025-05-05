#include <_printf.h>

const int MOD = 1000000007;
const int NMAX = 1001;
int dp[NMAX];

bool isInit = false;
static void init() {
    if (isInit) return;
    dp[0] = 1;
    dp[1] = 1;
    for (int i = 2; i < NMAX; i++) {
        dp[i] = 0;
        for (int j = i - 3; j >= 0; j--) {
            dp[i] += dp[j];
            if (dp[i] >= MOD) {
                dp[i] -= MOD;
            }
        }
        dp[i] <<= 1;
        if (dp[i] >= MOD) {
            dp[i] -= MOD;
        }
        dp[i] += dp[i - 1];
        if (dp[i] >= MOD) {
            dp[i] -= MOD;
        }
        dp[i] += dp[i - 2];
        if (dp[i] >= MOD) {
            dp[i] -= MOD;
        }
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