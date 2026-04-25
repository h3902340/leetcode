#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
class Solution {
   public:
    int compareBitonicSums(vector<int>& nums) {
        int n = nums.size();
        ll s1 = nums[0];
        int i = 1;
        for (; i < n; i++) {
            if (nums[i - 1] > nums[i]) {
                break;
            }
            s1 += nums[i];
        }
        ll s2 = nums[i - 1];
        for (; i < n; i++) {
            s2 += nums[i];
        }
        if (s1 > s2) {
            return 0;
        }
        if (s1 < s2) {
            return 1;
        }
        return -1;
    }
};

int main() {
    string problemName = "3909";
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
        auto res = sol.compareBitonicSums(nums);
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