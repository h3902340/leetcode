#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    vector<int> findValidElements(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) {
            return nums;
        }
        vector<int> suf(n);
        int r = nums[n - 1];
        suf[n - 1] = r;
        for (int i = n - 2; i >= 0; i--) {
            suf[i] = max(suf[i + 1], nums[i]);
        }
        vector<int> res;
        res.push_back(nums[0]);
        int l = nums[0];
        for (int i = 1; i < n - 1; i++) {
            if (l < nums[i] || nums[i] > suf[i + 1]) {
                res.push_back(nums[i]);
            }
            l = max(l, nums[i]);
        }
        res.push_back(nums[n - 1]);
        return res;
    }
};

int main() {
    string problemName = "3912";
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
        auto res = sol.findValidElements(nums);
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