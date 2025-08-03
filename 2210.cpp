#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    int countHillValley(vector<int>& nums) {
        int n = nums.size();
        int c = 0;
        int a = nums[0];
        int i = 1;
        while (i < n && a == nums[i]) {
            i++;
        }
        if (i == n) {
            return c;
        }
        bool isHill = false;
        if (a < nums[i]) {
            isHill = true;
        }
        a = nums[i];
        i++;
        for (; i < n; i++) {
            while (i < n && a == nums[i]) {
                i++;
            }
            if (i == n) {
                break;
            }
            if (isHill) {
                if (a > nums[i]) {
                    c++;
                    isHill = !isHill;
                }
            } else {
                if (a < nums[i]) {
                    c++;
                    isHill = !isHill;
                }
            }
            a = nums[i];
        }
        return c;
    }
};

int main() {
    string problemName = "2210";
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
        auto res = sol.countHillValley(nums);
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