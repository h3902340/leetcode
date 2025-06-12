#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int NMAX = 1e5;
char st[NMAX];

class Solution {
   public:
    string resultingString(string s) {
        int n = s.size();
        st[0] = s[0];
        int t = 0;
        for (int i = 1; i < n; i++) {
            if (t == -1) {
                st[++t] = s[i];
                continue;
            }
            if (abs(st[t] - s[i]) == 1 || abs(st[t] - s[i]) == 25) {
                t--;
            } else {
                st[++t] = s[i];
            }
        }
        string res = "";
        for (int i = 0; i <= t; i++) {
            res += st[i];
        }
        return res;
    }
};

int main() {
    string problemName = "3561";
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
        auto s = jread_string(line_in);
        auto res = sol.resultingString(s);
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