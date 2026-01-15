#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 5e4;
int cnt[N];
class Solution {
   public:
    int maximumAND(vector<int>& nums, int k, int m) {
        int n = nums.size();
        int res = 0;
        for (int mask = 1 << 30; mask > 0; mask >>= 1) {
            res ^= mask;
            for (int i = 0; i < n; i++) {
                int r = ~nums[i] & res;
                if (r == 0) {
                    cnt[i] = 0;
                } else {
                    int b = 32 - __builtin_clz(r);
                    int c = b == 31 ? INT32_MAX : (1 << b) - 1;
                    cnt[i] = (res & c) - (nums[i] & c);
                }
            }
            if (m < n) {
                nth_element(begin(cnt), begin(cnt) + m, begin(cnt) + n);
            }
            int a = 0;
            for (int i = 0; i < m; i++) {
                a += cnt[i];
                if (a > k) {
                    res ^= mask;
                    break;
                }
            }
        }
        return res;
    }
};

int main() {
    string problemName = "3806";
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
        getline(file_in, line_in);
        auto m = jread_int(line_in);
        auto res = sol.maximumAND(nums, k, m);
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