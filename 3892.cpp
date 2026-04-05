#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int K = 5000;
int dp[3][K + 1];
class Solution {
   public:
    int minOperations(vector<int>& nums, int k) {
        int n = nums.size();
        if (k == 0) {
            return 0;
        }
        if (k > n / 2) {
            return -1;
        }
        int x = f(0, n - 1, nums, n, k);
        int y = f(1, n, nums, n, k);
        return min(x, y);
    }
    int f(int l, int r, vector<int>& nums, int n, int k) {
        for (int i = 0; i < 3; i++) {
            dp[i][0] = 0;
            for (int j = 1; j <= k; j++) {
                dp[i][j] = -1;
            }
        }
        int x = 0;
        int y = 1;
        int z = 2;
        for (int i = l; i < r; i++) {
            int c = max(nums[(i - 1 + n) % n], nums[(i + 1) % n]);
            int a = 0;
            if (nums[i] <= c) {
                a = a + c - nums[i] + 1;
            }
            for (int j = 1; j <= k; j++) {
                if (dp[z][j - 1] != -1) {
                    dp[x][j] = dp[z][j - 1] + a;
                }
                if (dp[y][j] != -1) {
                    dp[x][j] = min(dp[x][j], dp[y][j]);
                }
            }
            int t = z;
            z = y;
            y = x;
            x = t;
        }
        return dp[y][k];
    }
};

int main() {
    string problemName = "3892";
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
        auto nums = jread_vector(line_in);
        getline(file_in, line_in);
        auto k = jread_int(line_in);
        auto res = sol.minOperations(nums, k);
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