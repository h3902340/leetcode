#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

vector<int> pre(2);
vector<int> cur(2);

class Solution {
   public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return nums[0];
        // not robbing house 0
        pre[0] = 0;
        pre[1] = nums[1];
        for (int i = 2; i < n; i++) {
            cur[0] = max(pre[1], pre[0]);
            cur[1] = pre[0] + nums[i];
            swap(pre, cur);
        }
        int best = max(pre[0], pre[1]);
        // rob house 0
        int best2 = nums[0];
        if (n > 3) {
            pre[0] = 0;
            pre[1] = nums[2];
            for (int i = 3; i < n - 1; i++) {
                cur[0] = max(pre[1], pre[0]);
                cur[1] = pre[0] + nums[i];
                swap(pre, cur);
            }
            best2 += max(pre[0], pre[1]);
        }
        return max(best, best2);
    }
};

int main() {
    string problemName = "213";
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
        auto res = sol.rob(nums);
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