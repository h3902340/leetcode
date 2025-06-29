#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 250;
int memo[N + 1][N + 1];
class Solution {
   public:
    int minXor(vector<int>& nums, int k) {
        int n = nums.size();
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                memo[i][j] = -1;
            }
        }
        return dfs(0, n, nums, k);
    }
    int dfs(int i, int n, vector<int>& nums, int k) {
        if (memo[i][k] != -1) {
            return memo[i][k];
        }
        int res = 0;
        if (k == 1) {
            for (int j = i; j < n; j++) {
                res ^= nums[j];
            }
            memo[i][k] = res;
            return res;
        }
        if (n - i == k) {
            for (int j = i; j < n; j++) {
                res = max(res, nums[j]);
            }
            memo[i][k] = res;
            return res;
        }
        res = INT32_MAX;
        int a = 0;
        for (int j = i; j < n; j++) {
            if (n - j < k) break;
            a ^= nums[j];
            int b = max(a, dfs(j + 1, n, nums, k - 1));
            res = min(res, b);
        }
        memo[i][k] = res;
        return res;
    }
};

int main() {
    string problemName = "3599";
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
        auto res = sol.minXor(nums, k);
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