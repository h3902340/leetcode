#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    string largestGoodInteger(string num) {
        int n = num.size();
        int c = 1;
        char d = num[0];
        char best = 0;
        for (int i = 1; i < n; i++) {
            if (d == num[i]) {
                c++;
                if (c == 3) {
                    if (best < d) {
                        best = d;
                    }
                    i++;
                    if (i < n) {
                        c = 1;
                        d = num[i];
                    }
                }
            } else {
                c = 1;
                d = num[i];
            }
        }
        if (best == 0) {
            return "";
        }
        string res(3, best);
        return res;
    }
};

int main() {
    string problemName = "2264";
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
        auto grid = jread_string(line_in);
        auto res = sol.largestGoodInteger(grid);
        getline(file_out, line_out);
        auto ans = jread_string(line_out);
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