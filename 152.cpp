#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size();
        int res = INT32_MIN;
        int i = 0;
        int p = 1;
        bool hasZero = false;
        for (int j = 0; j < n; j++) {
            if (nums[j] == 0) {
                hasZero = true;
                while (i < j && p < 0) {
                    p /= nums[i];
                    i++;
                }
                if (i < j) {
                    if (res < p) {
                        res = p;
                    }
                }
                i = j + 1;
                p = 1;
            } else {
                p *= nums[j];
                if (res < p) {
                    res = p;
                }
            }
        }
        while (i < n && p < 0) {
            p /= nums[i];
            i++;
        }
        if (i < n) {
            if (res < p) {
                res = p;
            }
        }
        if (hasZero) {
            if (res < 0) {
                res = 0;
            }
        }
        return res;
    }
};

int main() {
    string problemName = "152";
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
        auto res = sol.maxProduct(nums);
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