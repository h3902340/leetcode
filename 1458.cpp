#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int M = 500;
int dp[2][M];

class Solution {
   public:
    int maxDotProduct(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size();
        int n = nums2.size();
        dp[0][0] = nums1[0] * nums2[0];
        for (int i = 1; i < m; i++) {
            dp[0][i] = max(dp[0][i - 1], nums1[i] * nums2[0]);
        }
        bool p = 1;
        bool q = 0;
        for (int j = 1; j < n; j++) {
            dp[p][0] = max(dp[q][0], nums1[0] * nums2[j]);
            for (int i = 1; i < m; i++) {
                dp[p][i] = nums1[i] * nums2[j];
                if (dp[q][i - 1] > 0) {
                    dp[p][i] += dp[q][i - 1];
                }
                dp[p][i] = max(dp[p][i], dp[p][i - 1]);
                dp[p][i] = max(dp[p][i], dp[q][i]);
            }
            swap(p, q);
        }
        return dp[q][m - 1];
    }
};

int main() {
    string problemName = "1458";
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
        auto res = sol.maxDotProduct(nums1, nums2);
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