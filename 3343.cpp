#include <string>
#include <vector>
using namespace std;

const int MOD = 1e9 + 7;
const int COMP_MAX = 81;
const int D = 10;
const int EVEN_MAX = 41;
const int TARGET_MAX = 361;
int C[COMP_MAX][COMP_MAX];
int memo[D][EVEN_MAX][TARGET_MAX];
bool isInit = false;
static void init() {
    if (isInit) return;
    for (int i = 0; i < COMP_MAX; i++) {
        C[i][0] = 1;
        for (int j = 1; j < i; j++) {
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
            if (C[i][j] >= MOD) {
                C[i][j] -= MOD;
            }
        }
        C[i][i] = 1;
    }
    isInit = true;
}

class Solution {
   public:
    int cnt[10]{0};
    int evenCount;
    int oddCount;
    int prefix[10];
    int countBalancedPermutations(string num) {
        init();
        int n = num.size();
        int target = 0;
        oddCount = n >> 1;
        evenCount = n - oddCount;
        for (int i = 0; i < n; i++) {
            int d = num[i] - '0';
            cnt[d]++;
            target += d;
        }
        if (cnt[0] == n) {
            return 1;
        }
        prefix[0] = cnt[0];
        for (int i = 1; i < 10; i++) {
            prefix[i] = prefix[i - 1] + cnt[i];
        }
        if (target & 1) return 0;
        target >>= 1;
        for (int i = 0; i < D; i++) {
            for (int j = 0; j < EVEN_MAX; j++) {
                for (int k = 0; k < TARGET_MAX; k++) {
                    memo[i][j][k] = -1;
                }
            }
        }
        return subsetSum(0, 0, target);
    }

   private:
    int subsetSum(int i, int evenCur, int target) {
        if (target < 0) {
            return 0;
        }
        int evenRem = evenCount - evenCur;
        int oddCur = 0;
        if (i > 0) {
            oddCur = prefix[i - 1] - evenCur;
        }
        int oddRem = oddCount - oddCur;
        if (target == 0) {
            if (evenRem > 0) {
                return 0;
            }
            int res = 1;
            for (int j = i; j < 10; j++) {
                if (cnt[j] == 0) continue;
                oddCur += cnt[j];
                res = (long)res * C[oddCur][cnt[j]] % MOD;
            }
            return res;
        }
        while (i < 10 && cnt[i] == 0) {
            i++;
        }
        if (i == 10) {
            return 0;
        }
        if (memo[i][evenCur][target] != -1) {
            return memo[i][evenCur][target];
        }
        int ways = 0;
        int lo = max(0, cnt[i] - oddRem);
        int t = target - i * lo;
        for (int j = lo; j <= min(evenRem, cnt[i]); j++) {
            int k = cnt[i] - j;
            int way = (long)C[evenCur + j][j] * C[oddCur + k][k] % MOD;
            way = (long)way * subsetSum(i + 1, evenCur + j, t) % MOD;
            ways += way;
            if (ways >= MOD) {
                ways -= MOD;
            }
            if (t <= 0) break;
            t -= i;
        }
        memo[i][evenCur][target] = ways;
        return ways;
    }
};

// 2
/* string num = "123"; */

// 8
/* string num = "4567"; */

// 6
string num = "87113";

// 746355987
/* string num = "4974081081851759318027020355910663245333669190960558121217"; */

int main() {
    Solution sol;
    int ans = sol.countBalancedPermutations(num);
    printf("ans = %d\n", ans);
    return 0;
}