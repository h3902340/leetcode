#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int K = 1e4;
double dp[K];

class Solution {
   public:
    double new21Game(int n, int k, int maxPts) {
        if (k == 0) {
            return 1;
        }
        dp[0] = 1;
        for (int i = 1; i < k; i++) {
            int cap = min(i, maxPts);
            dp[i] = dp[i - 1];
            int l = i - cap;
            if (l > 0) {
                dp[i] -= dp[l - 1];
            }
            dp[i] /= maxPts;
            dp[i] += dp[i - 1];
        }
        for (int i = k - 1; i > 0; i--) {
            dp[i] -= dp[i - 1];
        }
        double res = 0;
        int lo = max(0, k - maxPts);
        for (int i = lo; i < k; i++) {
            int cap = min(i + maxPts, n);
            res += dp[i] * (cap - k + 1);
        }
        res /= maxPts;
        return res;
    }
};

int main() {
    string problemName = "837";
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
        auto k = jread_int(line_in);
        getline(file_in, line_in);
        auto maxPts = jread_int(line_in);
        auto res = sol.new21Game(n, k, maxPts);
        getline(file_out, line_out);
        auto ans = jread_double(line_out);
        printf("Case %d", ++caseCount);
        const int tol = 1e5;
        int resInt = (int)(res * tol);
        int ansInt = (int)(ans * tol);
        if (ansInt - 1 <= resInt && resInt <= ansInt + 1) {
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