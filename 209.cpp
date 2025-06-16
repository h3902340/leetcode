#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size();
        int res = 0;
        int i = 0;
        int a = 0;
        for (int j = 0; j < n; j++) {
            a += nums[j];
            while (i < j && a >= target) {
                if (a - nums[i] < target) {
                    break;
                }
                a -= nums[i];
                i++;
            }
            if (a >= target) {
                int len = j - i + 1;
                if (res == 0 || res > len) {
                    res = len;
                }
            }
        }
        return res;
    }
};

int main() {
    string problemName = "209";
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
        auto target = jread_int(line_in);
        getline(file_in, line_in);
        auto nums = jread_vector(line_in);
        auto res = sol.minSubArrayLen(target, nums);
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