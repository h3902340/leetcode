#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    bool isTrionic(vector<int>& nums) {
        int n = nums.size();
        int cur = nums[0];
        int i = 1;
        for (; i < n; i++) {
            if (cur >= nums[i]) {
                break;
            }
            cur = nums[i];
        }
        i--;
        if (i == 0) {
            return false;
        }
        if (i == n) {
            return false;
        }
        int p = i;
        cur = nums[i];
        i++;
        for (; i < n; i++) {
            if (cur <= nums[i]) {
                break;
            }
            cur = nums[i];
        }
        i--;
        if (i == n) {
            return false;
        }
        int q = i;
        if (p == q || q == n - 1) {
            return false;
        }
        cur = nums[i];
        i++;
        for (; i < n; i++) {
            if (cur >= nums[i]) {
                break;
            }
            cur = nums[i];
        }
        if (i != n) {
            return false;
        }
        return true;
    }
};

int main() {
    string problemName = "3637";
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
        auto res = sol.isTrionic(nums);
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