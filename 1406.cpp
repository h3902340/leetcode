#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 5e4;
int memo[N];

class Solution {
   public:
    string stoneGameIII(vector<int>& stoneValue) {
        int n = stoneValue.size();
        for (int i = 0; i < n; i++) {
            memo[i] = INT32_MIN;
        }
        for (int i = 1; i < n; i++) {
            stoneValue[i] += stoneValue[i - 1];
        }
        int a = dfs(0, n, stoneValue);
        int b = stoneValue[n - 1] - a;
        if (a > b) {
            return "Alice";
        }
        if (a < b) {
            return "Bob";
        }
        return "Tie";
    }
    int dfs(int i, int n, vector<int>& stoneValue) {
        if (memo[i] != INT32_MIN) {
            return memo[i];
        }
        int sum = stoneValue[n - 1];
        if (i > 0) {
            sum -= stoneValue[i - 1];
        }
        int res = INT32_MIN;
        for (int j = 1; j <= 3; j++) {
            if (i + j == n) {
                if (res < sum) {
                    res = sum;
                }
                break;
            }
            int a = sum - dfs(i + j, n, stoneValue);
            if (res < a) {
                res = a;
            }
        }
        memo[i] = res;
        return res;
    }
};

int main() {
    string problemName = "1406";
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
        auto stoneValue = jread_vector(line_in);
        auto res = sol.stoneGameIII(stoneValue);
        getline(file_out, line_out);
        auto ans = jread_string(line_out);
        printf("Case %d", ++caseCount);
        if (res == ans) {
            passCount++;
            printf(" %s(PASS)", KGRN);
        } else {
            printf(" %s(WRONG)", KRED);
            allPass = false;
        }
        printf("\n%s", KNRM);
        jprint_string(res, "res");
        jprint_string(ans, "ans");
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