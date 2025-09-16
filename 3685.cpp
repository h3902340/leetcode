#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

// TODO: someone has faster solution
const int K = 4e3;
bool dp[K + 1];
class Solution {
   public:
    vector<bool> subsequenceSumAfterCapping(vector<int>& nums, int k) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        vector<bool> res(n);
        for (int i = 1; i <= k; i++) {
            dp[i] = false;
        }
        dp[0] = true;
        int i = 0;
        for (int x = 1; x <= n; x++) {
            while (i < n && nums[i] < x) {
                for (int w = k; w >= nums[i]; w--) {
                    if (dp[w]) {
                        continue;
                    }
                    dp[w] = dp[w - nums[i]];
                }
                i++;
            }
            if (dp[k]) {
                res[x - 1] = true;
                continue;
            }
            int cap = n - i;
            int w = k;
            for (int j = 1; j <= cap; j++) {
                w -= x;
                if (w < 0) {
                    break;
                }
                if (dp[w]) {
                    res[x - 1] = true;
                    break;
                }
            }
        }
        return res;
    }
};

int main() {
    string problemName = "3685";
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
        auto res = sol.subsequenceSumAfterCapping(nums, k);
        getline(file_out, line_out);
        auto ans = jread_vector_bool(line_out);
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