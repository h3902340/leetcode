#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    long long distributeCandies(int n, int limit) {
        long long res = (long long)(n + 2) * (n + 1);
        int exceed = limit + 1;
        if (n >= exceed) {
            res -= (long long)(n - exceed + 2) * (n - exceed + 1) * 3;
        }
        exceed += limit + 1;
        if (n >= exceed) {
            res += (long long)(n - exceed + 2) * (n - exceed + 1) * 3;
        }
        exceed += limit + 1;
        if (n >= exceed) {
            res -= (long long)(n - exceed + 2) * (n - exceed + 1);
        }
        return res >> 1;
    }
};

int main() {
    string problemName = "2929";
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
        auto limit = jread_int(line_in);
        auto res = sol.distributeCandies(n, limit);
        getline(file_out, line_out);
        auto ans = jread_longlong(line_out);
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