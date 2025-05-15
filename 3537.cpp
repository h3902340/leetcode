#include <unordered_set>
#include <vector>
using namespace std;

// TODO: time can be slightly faster (9 ms, beat 66.33%)
const int NMAX = 11;
vector<vector<vector<int>>> dp(NMAX);
bool isInit = false;
static void init() {
    if (isInit) return;
    dp[0] = {{0}};
    int s = 1;
    for (int i = 1; i < NMAX; i++) {
        int s_pre = s;
        int s_pre_square = s * s;
        s <<= 1;
        dp[i] = vector<vector<int>>(s, vector<int>(s));
        for (int j = 0; j < s_pre; j++) {
            for (int k = 0; k < s_pre; k++) {
                dp[i][j][s_pre + k] = dp[i - 1][j][k];
                dp[i][s_pre + j][s_pre + k] = dp[i - 1][j][k] + s_pre_square;
                dp[i][s_pre + j][k] = dp[i - 1][j][k] + s_pre_square * 2;
                dp[i][j][k] = dp[i - 1][j][k] + s_pre_square * 3;
            }
        }
    }
    isInit = true;
}

class Solution {
   public:
    vector<vector<int>> specialGrid(int N) {
        init();
        return dp[N];
    }
};

int N = 2;

int main() {
    Solution sol;
    vector<vector<int>> ans = sol.specialGrid(N);
    for (int j = 0; j < ans.size(); j++) {
        printf("ans = [%d", ans[j][0]);
        for (int i = 1; i < ans.size(); i++) {
            printf(",%d", ans[j][i]);
        }
        printf("]\n");
    }
    return 0;
}