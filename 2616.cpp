#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    int minimizeMax(vector<int>& nums, int p) {
        if (p == 0) return 0;
        int n = nums.size();
        sort(nums.begin(), nums.end());
        int l = INT32_MAX;
        int r = INT32_MIN;
        for (int i = 1; i < n; i++) {
            int d = nums[i] - nums[i - 1];
            nums[i - 1] = d;
            if (l > d) {
                l = d;
            }
            if (r < d) {
                r = d;
            }
        }
        int res = r;
        while (l <= r) {
            int mid = (l + r) >> 1;
            int c = 0;
            for (int i = 0; i < n - 1; i++) {
                if (nums[i] <= mid) {
                    c++;
                    i++;
                }
            }
            if (c < p) {
                l = mid + 1;
            } else {
                r = mid - 1;
                res = mid;
            }
        }
        return res;
    }
};

int main() {
    string problemName = "2616";
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
        auto p = jread_int(line_in);
        auto res = sol.minimizeMax(nums, p);
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