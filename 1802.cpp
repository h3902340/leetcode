#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
class Solution {
   public:
    int maxValue(int n, int index, int maxSum) {
        int res = 1;
        int l = 1;
        int r = maxSum;
        int end = n - index - 1;
        while (l <= r) {
            int mid = (l + r) >> 1;
            ll c = (ll)mid * mid;
            if (mid > index) {
                c -= (ll)(mid - index) * (mid - index - 1) >> 1;
            } else {
                c += index - mid + 1;
            }
            if (mid > end) {
                c -= (ll)(mid - end) * (mid - end - 1) >> 1;
            } else {
                c += end - mid + 1;
            }
            if (c > maxSum) {
                r = mid - 1;
            } else {
                l = mid + 1;
                res = mid;
            }
        }
        return res;
    }
};

int main() {
    string problemName = "1802";
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
        auto n = jread_int(line_in);
        getline(file_in, line_in);
        auto index = jread_int(line_in);
        getline(file_in, line_in);
        auto maxSum = jread_int(line_in);
        auto res = sol.maxValue(n, index, maxSum);
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