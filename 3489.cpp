#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int M = 1000;
const int NUM = 1000;
int dp[M + 1][NUM + 1];

class Solution {
   public:
    int minZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        int m = queries.size();
        int max = 0;
        for (int i = 0; i < n; i++) {
            int w = nums[i];
            int k = knapsack(i, w, m, queries);
            if (k == -1) {
                return -1;
            }
            if (max < k) {
                max = k;
            }
        }
        return max;
    }
    int knapsack(int i, int w, int k, vector<vector<int>>& queries) {
        for (int y = 0; y <= w; y++) {
            dp[0][y] = 0;
        }
        if (dp[0][w] == w) {
            return 0;
        }
        for (int x = 0; x < k; x++) {
            int l = queries[x][0];
            int r = queries[x][1];
            int v = queries[x][2];
            if (i < l || i > r) {
                for (int y = 0; y <= w; y++) {
                    dp[x + 1][y] = dp[x][y];
                }
                continue;
            }
            for (int y = 0; y <= w; y++) {
                if (y < v) {
                    dp[x + 1][y] = dp[x][y];
                } else {
                    dp[x + 1][y] = max(dp[x][y], dp[x][y - v] + v);
                }
            }
            if (dp[x + 1][w] == w) {
                return x + 1;
            }
        }
        return -1;
    }
};

int main() {
    string problemName = "3489";
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
        auto queries = jread_vector2d(line_in);
        auto res = sol.minZeroArray(nums, queries);
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
        jprint_vector(nums, "nums");
        jprint_vector2d(queries, "queries");
        jprint_int(res, "res");
        jprint_int(ans, "ans");
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