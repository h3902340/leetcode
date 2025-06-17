#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int NUMLO = 0;
const int NUMHI = 1e5;
const int K = 1e5;
int interval[NUMHI - NUMLO + K * 2 + 2];
class Solution {
   public:
    int maximumBeauty(vector<int>& nums, int k) {
        int n = nums.size();
        int lo = NUMHI + 1;
        int hi = NUMLO - 1;
        for (int i = 0; i < n; i++) {
            if (lo > nums[i]) {
                lo = nums[i];
            }
            if (hi < nums[i]) {
                hi = nums[i];
            }
        }
        for (int i = 0; i < hi - lo + k * 2 + 2; i++) {
            interval[i] = 0;
        }
        for (int i = 0; i < n; i++) {
            interval[nums[i] - lo]++;
            interval[nums[i] - lo + k * 2 + 1]--;
        }
        int maxCount = interval[0];
        for (int i = 1; i < hi - lo + k * 2 + 2; i++) {
            interval[i] += interval[i - 1];
            if (maxCount < interval[i]) {
                maxCount = interval[i];
            }
        }
        return maxCount;
    }
};

int main() {
    string problemName = "2779";
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
        auto k = jread_int(line_in);
        auto res = sol.maximumBeauty(nums, k);
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