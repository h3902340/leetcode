#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    long long maximumProduct(vector<int>& nums, int m) {
        int n = nums.size();
        long long res = (long long)nums[0] * nums[m - 1];
        int leftMax = nums[0];
        int leftMin = nums[0];
        int j = 1;
        for (int i = m; i < n; i++) {
            if (leftMax < nums[j]) {
                leftMax = nums[j];
            }
            if (leftMin > nums[j]) {
                leftMin = nums[j];
            }
            long long prod = (long long)leftMax * nums[i];
            if (res < prod) {
                res = prod;
            }
            prod = (long long)leftMin * nums[i];
            if (res < prod) {
                res = prod;
            }
            j++;
        }
        return res;
    }
};

int main() {
    string problemName = "3584";
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
        auto m = jread_int(line_in);
        auto res = sol.maximumProduct(nums, m);
        getline(file_out, line_out);
        auto ans = jread_longlong(line_out);
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