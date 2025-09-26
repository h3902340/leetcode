#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int U = 1000;
int cnt[U + 1];

class Solution {
   public:
    int triangleNumber(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i <= U; i++) {
            cnt[i] = 0;
        }
        int lo = U + 1;
        int hi = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i] == 0) {
                continue;
            }
            cnt[nums[i]]++;
            if (lo > nums[i]) {
                lo = nums[i];
            }
            if (hi < nums[i]) {
                hi = nums[i];
            }
        }
        int res = 0;
        for (int k = lo; k <= hi; k++) {
            int i = 2;
            int j = k - 1;
            int c = 0;
            while (i <= j) {
                int b = cnt[j] - cnt[j - 1];
                if (b > 0) {
                    c += (cnt[j - 1] - cnt[i - 1]) * b + (b * (b - 1) >> 1);
                }
                i++;
                j--;
            }
            res += c * cnt[k];
            int t = cnt[k] * (cnt[k] - 1) >> 1;
            res += cnt[k - 1] * t;
            res += t * (cnt[k] - 2) / 3;
            cnt[k] += cnt[k - 1];
        }
        return res;
    }
};

int main() {
    string problemName = "611";
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
        auto res = sol.triangleNumber(nums);
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