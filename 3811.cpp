#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int MOD = 1e9 + 7;
int add(int a, int b) {
    a += b;
    if (a >= MOD) {
        a -= MOD;
    }
    return a;
}
int val[4];
int dp[2][4];

class Solution {
   public:
    int alternatingXOR(vector<int>& nums, int target1, int target2) {
        int n = nums.size();
        int a = 0;
        val[0] = target1;
        val[1] = target1 ^ target2;
        val[2] = target2;
        val[3] = 0;
        for (int i = 0; i < 4; i++) {
            dp[0][i] = 0;
        }
        bool p = 0;
        bool q = 1;
        int res = 0;
        for (int i = 0; i < n; i++) {
            a ^= nums[i];
            if (a == val[0]) {
                dp[q][0] = 1 + dp[p][3];
            } else {
                dp[q][0] = 0;
            }
            for (int j = 1; j < 4; j++) {
                if (a == val[j]) {
                    dp[q][j] = dp[p][j - 1];
                } else {
                    dp[q][j] = 0;
                }
            }
            if (i == n - 1) {
                for (int j = 0; j < 4; j++) {
                    res = add(res, dp[q][j]);
                }
                return res;
            }
            for (int j = 0; j < 4; j++) {
                dp[q][j] = add(dp[q][j], dp[p][j]);
            }
            swap(p, q);
        }
        return res;
    }
};

int main() {
    string problemName = "3811";
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
        auto target1 = jread_int(line_in);
        getline(file_in, line_in);
        auto target2 = jread_int(line_in);
        auto res = sol.alternatingXOR(nums, target1, target2);
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