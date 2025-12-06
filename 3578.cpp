#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int MOD = 1e9 + 7;
const int N = 5e4;

int dp[N + 2];
int qmax[N];
int qmin[N];

class Solution {
public:
    int countPartitions(vector<int>& nums, int k) {
        int n = nums.size();
        int lmax = 0;
        int rmax = -1;
        int lmin = 0;
        int rmin = -1;
        int i = 0;
        dp[0] = -1;
        dp[1] = 0;
        for (int j = 0; j < n; j++) {
            while (lmax <= rmax && qmax[rmax] < nums[j]) {
                rmax--;
            }
            while (lmin <= rmin && qmin[rmin] > nums[j]) {
                rmin--;
            }
            qmax[++rmax] = nums[j];
            qmin[++rmin] = nums[j];
            while (qmax[lmax] - qmin[lmin] > k) {
                if (qmax[lmax] == nums[i]) {
                    lmax++;
                }
                if (qmin[lmin] == nums[i]) {
                    lmin++;
                }
                i++;
            }
            dp[j + 2] = ((dp[j + 1] << 1) - dp[i]) % MOD;
            if (dp[j + 2] < 0) {
                dp[j + 2] += MOD;
            }
        }
        int res = dp[n + 1] - dp[n];
        if (res < 0) {
            res += MOD;
        }
        return res;
    }
};

int main() {
    string problemName = "3578";
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
        auto res = sol.countPartitions(nums, k);
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