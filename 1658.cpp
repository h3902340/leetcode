#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    int minOperations(vector<int>& nums, int x) {
        int n = nums.size();
        int i = 0;
        int j = n - 1;
        while (i < n && x > 0) {
            x -= nums[i];
            i++;
        }
        int res = -1;
        if (x > 0) return res;
        if (x == 0) {
            res = i;
        }
        if (i == n) return res;
        while (i > 0) {
            i--;
            x += nums[i];
            while (x > 0) {
                x -= nums[j];
                j--;
            }
            if (x == 0) {
                int a = i + n - 1 - j;
                if (res == -1 || res > a) {
                    res = a;
                }
            } else {
                j++;
                x += nums[j];
            }
        }
        return res;
    }
};

int main() {
    string problemName = "1658";
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
        auto x = jread_int(line_in);
        auto res = sol.minOperations(nums, x);
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