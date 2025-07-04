#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    int splitArray(vector<int>& nums, int k) {
        int n = nums.size();
        int l = 0;
        int r = 0;
        for (int i = 0; i < n; i++) {
            l = max(l, nums[i]);
            r += nums[i];
        }
        int res = r;
        while (l <= r) {
            int mid = (l + r) >> 1;
            int sum = 0;
            int a = k;
            bool fail = false;
            for (int i = 0; i < n; i++) {
                if (nums[i] > mid) {
                    fail = true;
                    break;
                }
                sum += nums[i];
                if (sum > mid) {
                    if (a == 1) {
                        fail = true;
                        break;
                    }
                    sum = nums[i];
                    a--;
                }
            }
            if (fail) {
                l = mid + 1;
            } else {
                res = mid;
                r = mid - 1;
            }
        }
        return res;
    }
};

int main() {
    string problemName = "410";
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
        auto res = sol.splitArray(nums, k);
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