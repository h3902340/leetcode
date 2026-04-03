#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 300;
int dp[N + 1][N];
int arr[N + 2];
class Solution {
   public:
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        arr[0] = 1;
        arr[n + 1] = 1;
        for (int i = 0; i < n; i++) {
            arr[i + 1] = nums[i];
        }
        for (int i = 1; i <= n; i++) {
            dp[i][0] = arr[i - 1] * arr[i] * arr[i + 1];
        }
        for (int l = 1; l < n; l++) {
            for (int i = 1; i + l <= n; i++) {
                dp[i][l] = max(
                    arr[i - 1] * arr[i] * arr[i + l + 1] + dp[i + 1][l - 1],
                    dp[i][l - 1] + arr[i - 1] * arr[i + l] * arr[i + l + 1]);
                for (int j = i + 1; j < i + l; j++) {
                    dp[i][l] =
                        max(dp[i][l], dp[i][j - i - 1] +
                                          arr[i - 1] * arr[j] * arr[l + i + 1] +
                                          dp[j + 1][l - 1 - j + i]);
                }
            }
        }
        return dp[1][n - 1];
    }
};

int main() {
    string problemName = "312";
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
        auto res = sol.maxCoins(nums);
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