#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

// based on lee's solution
class Solution {
   public:
    int minOperations(string s1, string s2, int x) {
        int n = s1.size();
        int i = 0;
        while (i < n && s1[i] == s2[i]) {
            i++;
        }
        if (i == n) {
            return 0;
        }
        // The costs of flipping are doubled for both operations, then divided
        // by 2 in the end.
        // The cost of flipping two characters directly is cut in half, it is
        // the cost for flipping a single character. If the number of
        // differences is odd, s1 can't be transformed into s2. So cutting x in
        // half won't affect the outcome since the flipping operations will all
        // be paired. Let dp[i] be the min cost for the first i differences.
        // Let a[i] be the cost of "continuous flip" from the i-th difference to
        // the (i+1)-th difference. Then, dp[i]=min{dp[i-2]+a[i-1],dp[i-1]+x}.
        // Because only dp[i-1] and dp[i-2] are used to construct dp[i], the dp
        // can be compressed into 2 variables. pre = dp[i-2], cur = dp[i-1].
        int pre = 0;
        int cur = x;
        bool isOdd = true;
        i++;
        for (; i < n; i++) {
            pre += 2;
            if (s1[i] != s2[i]) {
                int tmp = cur;
                cur = min(cur + x, pre);
                pre = tmp;
                isOdd = !isOdd;
            }
        }
        if (isOdd) {
            return -1;
        }
        return cur >> 1;
    }
};

int main() {
    string problemName = "2896";
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
        auto s1 = jread_string(line_in);
        getline(file_in, line_in);
        auto s2 = jread_string(line_in);
        getline(file_in, line_in);
        auto x = jread_int(line_in);
        auto res = sol.minOperations(s1, s2, x);
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