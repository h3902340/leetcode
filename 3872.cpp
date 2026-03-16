#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 1e5;
int l[N];
int r[N];

class Solution {
   public:
    int longestArithmetic(vector<int>& nums) {
        int n = nums.size();
        l[0] = 1;
        l[1] = 2;
        for (int i = 2; i < n; i++) {
            if (nums[i] - nums[i - 1] == nums[i - 1] - nums[i - 2]) {
                l[i] = l[i - 1] + 1;
            } else {
                l[i] = 2;
            }
        }
        r[n - 1] = 1;
        r[n - 2] = 2;
        for (int i = n - 3; i >= 0; i--) {
            if (nums[i] - nums[i + 1] == nums[i + 1] - nums[i + 2]) {
                r[i] = r[i + 1] + 1;
            } else {
                r[i] = 2;
            }
        }
        int res = max(1 + l[n - 2], 1 + r[1]);
        for (int i = 1; i < n - 1; i++) {
            res = max(res, 1 + l[i - 1]);
            res = max(res, 1 + r[i + 1]);
            if ((nums[i - 1] + nums[i + 1]) % 2 == 0) {
                int mid = (nums[i - 1] + nums[i + 1]) >> 1;
                int a = 1;
                if (i == 1 || nums[i - 1] - nums[i - 2] == mid - nums[i - 1]) {
                    a = l[i - 1];
                }
                int b = 1;
                if (i == n - 2 ||
                    nums[i + 2] - nums[i + 1] == nums[i + 1] - mid) {
                    b = r[i + 1];
                }
                res = max(res, a + 1 + b);
            }
        }
        return res;
    }
};

int main() {
    string problemName = "3872";
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
        auto res = sol.longestArithmetic(nums);
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