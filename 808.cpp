#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int TOL = 1e7;
const int HALF = TOL >> 1;
const int CAP = 179;
int memo[CAP][CAP];
bool isInit = false;
static void init() {
    for (int i = 1; i < CAP; i++) {
        for (int j = 1; j < CAP; j++) {
            memo[i][j] = -1;
        }
    }
    isInit = true;
}
class Solution {
   public:
    double soupServings(int n) {
        if (!isInit) {
            init();
        }
        int a = (n + 24) / 25;
        if (a >= CAP) {
            return 1;
        }
        return (double)f(a, a) / TOL;
    }
    int f(int a, int b) {
        if (a <= 0 && b <= 0) {
            return HALF;
        }
        if (a <= 0) {
            return TOL;
        }
        if (b <= 0) {
            return 0;
        }
        if (memo[a][b] != -1) {
            return memo[a][b];
        }
        int res = (f(a - 4, b) + f(a - 3, b - 1) + f(a - 2, b - 2) +
                   f(a - 1, b - 3)) >>
                  2;
        memo[a][b] = res;
        return res;
    }
};

int main() {
    string problemName = "808";
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
        auto res = sol.soupServings(n);
        getline(file_out, line_out);
        auto ans = jread_double(line_out);
        printf("Case %d", ++caseCount);
        if ((int)(res * 100000) == (int)(ans * 100000)) {
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