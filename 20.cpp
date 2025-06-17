#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 1e4;
char st[N];
class Solution {
   public:
    bool isValid(string s) {
        int n = s.size();
        int r = 0;
        st[r] = s[0];
        for (int i = 1; i < n; i++) {
            if (isClosed(s[i])) {
                if (r == -1) {
                    return false;
                }
                if (isSameType(st[r], s[i])) {
                    r--;
                } else {
                    return false;
                }
            } else {
                st[++r] = s[i];
            }
        }
        if (r >= 0) {
            return false;
        }
        return true;
    }
    bool isClosed(char b) { return b == ')' || b == ']' || b == '}'; }
    bool isSameType(char a, char b) {
        return (a == '(' && b == ')') || (a == '[' && b == ']') ||
               (a == '{' && b == '}');
    }
};

int main() {
    string problemName = "20";
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
        auto res = sol.isValid(s);
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