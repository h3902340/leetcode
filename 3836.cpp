#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
const int N = 100;
const int M = 100;
const int K = 100;
ll dp[N][M][K];

class Solution {
   public:
    long long maxScore(vector<int>& nums1, vector<int>& nums2, int k) {
        int n = nums1.size();
        int m = nums2.size();
        for (int i = n - 1; i >= 0; i--) {
            for (int j = m - 1; j >= 0; j--) {
                dp[i][j][0] = (ll)nums1[i] * nums2[j];
                for (int l = 1; l < k; l++) {
                    if (min(n - i - 1, m - j - 1) > l - 1) {
                        dp[i][j][l] = dp[i][j][0] + dp[i + 1][j + 1][l - 1];
                    }
                    if (min(n - i - 1, m - j) > l) {
                        dp[i][j][l] = max(dp[i][j][l], dp[i + 1][j][l]);
                    }
                    if (min(n - i, m - j - 1) > l) {
                        dp[i][j][l] = max(dp[i][j][l], dp[i][j + 1][l]);
                    }
                }
                if (i + 1 < n) {
                    dp[i][j][0] = max(dp[i][j][0], dp[i + 1][j][0]);
                }
                if (j + 1 < m) {
                    dp[i][j][0] = max(dp[i][j][0], dp[i][j + 1][0]);
                }
            }
        }
        return dp[0][0][k - 1];
    }
};

int main() {
    string problemName = "3836";
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
        auto nums1 = jread_vector(line_in);
        getline(file_in, line_in);
        auto nums2 = jread_vector(line_in);
        getline(file_in, line_in);
        auto k = jread_int(line_in);
        auto res = sol.maxScore(nums1, nums2, k);
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