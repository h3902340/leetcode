#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    int sortableIntegers(vector<int>& nums) {
        int n = nums.size();
        int res = 1;
        int x = 1;
        for (; x < n; x++) {
            if (nums[x] < nums[x - 1]) {
                res = 0;
                break;
            }
        }
        if (res == 1) {
            for (int i = 2; i <= n; i++) {
                if (n % i == 0) {
                    res += i;
                }
            }
            return res;
        }
        for (int l = 2; l <= n; l++) {
            if (n % l != 0) {
                continue;
            }
            bool fail = false;
            int a = 0;
            for (int i = 0; i < n; i += l) {
                int pre = 0;
                bool once = true;
                int mx = 0;
                for (int j = i; j < i + l; j++) {
                    mx = max(mx, nums[j]);
                    if (!once) {
                        if (nums[j] > nums[i]) {
                            fail = true;
                            break;
                        }
                    }
                    if (nums[j] < pre) {
                        if (!once) {
                            fail = true;
                            break;
                        }
                        once = false;
                        if (nums[j] < a) {
                            fail = true;
                            break;
                        }
                        if (nums[j] > nums[i]) {
                            fail = true;
                            break;
                        }
                    }
                    pre = nums[j];
                }
                if (once) {
                    if (nums[i] < a) {
                        fail = true;
                    }
                }
                if (fail) {
                    break;
                }
                a = mx;
            }
            if (!fail) {
                res += l;
            }
        }
        return res;
    }
};

int main() {
    string problemName = "3886";
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
        auto res = sol.sortableIntegers(nums);
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