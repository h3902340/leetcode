#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    int myAtoi(string s) {
        int n = s.size();
        int res = 0;
        bool isNeg = false;
        int start = 0;
        while (start < n && s[start] == ' ') {
            start++;
        }
        for (int i = start; i < n; i++) {
            if (s[i] < '0' || s[i] > '9') {
                if (i == start) {
                    if (s[i] == '-') {
                        isNeg = true;
                    } else if (s[i] == '+') {
                        isNeg = false;
                    } else {
                        break;
                    }
                    continue;
                }
                break;
            }
            if (isNeg) {
                if (INT32_MIN / 10 > res || (INT32_MIN / 10 == res &&
                                             -(INT32_MIN % 10) <= s[i] - '0')) {
                    res = INT32_MIN;
                    break;
                }
                res = res * 10 - (s[i] - '0');
            } else {
                if (INT32_MAX / 10 < res ||
                    (INT32_MAX / 10 == res && INT32_MAX % 10 <= s[i] - '0')) {
                    res = INT32_MAX;
                    break;
                }
                res = res * 10 + (s[i] - '0');
            }
        }
        return res;
    }
};

int main() {
    string problemName = "8";
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
        auto res = sol.myAtoi(s);
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