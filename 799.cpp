#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int C = 100;
double dp[C];

class Solution {
   public:
    double champagneTower(int poured, int query_row, int query_glass) {
        dp[0] = poured;
        for (int i = 0; i < query_row; i++) {
            dp[i + 1] = 0;
            for (int j = i; j >= 0; j--) {
                if (dp[j] < 1) {
                    dp[j] = 0;
                    continue;
                }
                double half = .5f * (dp[j] - 1);
                dp[j + 1] += half;
                dp[j] = half;
            }
        }
        double res = dp[query_glass];
        if (res > 1) {
            res = 1;
        }
        return res;
    }
};

int main() {
    string problemName = "799";
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
        auto poured = jread_int(line_in);
        getline(file_in, line_in);
        auto query_row = jread_int(line_in);
        getline(file_in, line_in);
        auto query_glass = jread_int(line_in);
        auto res = sol.champagneTower(poured, query_row, query_glass);
        getline(file_out, line_out);
        auto ans = jread_double(line_out);
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