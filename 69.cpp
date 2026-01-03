#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define lg2(n) (32 - __builtin_clz(n))
class Solution {
   public:
    int mySqrt(int x) {
        if (x == 0) {
            return 0;
        }
        int l = 0;
        int b = lg2(x);
        int r = min(46340, 1 << ((b >> 1) + (b & 1)));
        int mx = 0;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (mid * mid > x) {
                r = mid - 1;
            } else {
                mx = mid;
                l = mid + 1;
            }
        }
        return mx;
    }
};

int main() {
    string problemName = "69";
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
        auto x = jread_int(line_in);
        auto res = sol.mySqrt(x);
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