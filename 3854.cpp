#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    vector<int> makeParityAlternating(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) {
            return {0, 0};
        }
        int a = 0;
        int mn = 1e9 + 1;
        int mx = -1e9 - 1;
        int mni = -1;
        int mxi = -1;
        int d1 = 0;
        int d2 = 0;
        for (int i = 0; i < n; i++) {
            bool alter = false;
            if ((i & 1) && (nums[i] & 1)) {
                a++;
                alter = true;
            } else if ((i & 1) == 0 && (nums[i] & 1) == 0) {
                a++;
                alter = true;
            }
            if (mn > nums[i]) {
                mn = nums[i];
                mni = i;
                d1 = alter;
            } else if (mn == nums[i] && (mni & 1) != (i & 1)) {
                d1 = 0;
            }
            if (mx < nums[i]) {
                mx = nums[i];
                mxi = i;
                d2 = alter;
            } else if (mx == nums[i] && (mxi & 1) != (i & 1)) {
                d2 = 0;
            }
        }
        if (mn == mx) {
            return {n >> 1, 1};
        }
        vector<int> res1 = {a, mx - d1 - mn - d2};
        a = 0;
        mn = 1e9 + 1;
        mx = -1e9 - 1;
        mni = -1;
        mxi = -1;
        d1 = 0;
        d2 = 0;
        for (int i = 0; i < n; i++) {
            bool alter = false;
            if ((i & 1) && (nums[i] & 1) == 0) {
                a++;
                alter = true;
            } else if ((i & 1) == 0 && (nums[i] & 1)) {
                a++;
                alter = true;
            }
            if (mn > nums[i]) {
                mn = nums[i];
                mni = i;
                d1 = alter;
            } else if (mn == nums[i] && (mni & 1) != (i & 1)) {
                d1 = 0;
            }
            if (mx < nums[i]) {
                mx = nums[i];
                mxi = i;
                d2 = alter;
            } else if (mx == nums[i] && (mxi & 1) != (i & 1)) {
                d2 = 0;
            }
        }
        vector<int> res2 = {a, mx - d1 - mn - d2};
        if (res1[0] < res2[0]) {
            return res1;
        } else if (res1[0] > res2[0]) {
            return res2;
        } else {
            if (res1[1] < res2[1]) {
                return res1;
            }
        }
        return res2;
    }
};

int main() {
    string problemName = "3854";
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
        auto res = sol.makeParityAlternating(nums);
        getline(file_out, line_out);
        auto ans = jread_vector(line_out);
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