#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

int leaderboard[3][3];

class Solution {
   public:
    int maximumSum(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                leaderboard[i][j] = 0;
            }
        }
        for (int i = 0; i < n; i++) {
            int r = nums[i] % 3;
            if (leaderboard[r][2] < nums[i]) {
                leaderboard[r][2] = nums[i];
                for (int j = 2; j >= 1; j--) {
                    if (leaderboard[r][j] > leaderboard[r][j - 1]) {
                        swap(leaderboard[r][j], leaderboard[r][j - 1]);
                    }
                }
            }
        }
        // 000,012,111,222
        int res = 0;
        for (int i = 0; i < 3; i++) {
            if (leaderboard[i][0] == 0) {
                res = 0;
                break;
            }
            res += leaderboard[i][0];
        }
        for (int i = 0; i < 3; i++) {
            int a = 0;
            for (int j = 0; j < 3; j++) {
                if (leaderboard[i][j] == 0) {
                    a = 0;
                    break;
                }
                a += leaderboard[i][j];
            }
            if (res < a) {
                res = a;
            }
        }
        return res;
    }
};

int main() {
    string problemName = "3780";
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
        auto res = sol.maximumSum(nums);
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