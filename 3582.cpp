#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    string generateTag(string caption) {
        string res = "#";
        bool first = true;
        bool wordFirst = true;
        for (auto e : caption) {
            if (e == ' ') {
                wordFirst = true;
                continue;
            }
            if (first) {
                if (e <= 'Z') {
                    res += (e - 'A' + 'a');
                } else {
                    res += e;
                }
                first = false;
                wordFirst = false;
                continue;
            }
            if (wordFirst) {
                if (e >= 'a') {
                    res += (e - 'a' + 'A');
                } else {
                    res += e;
                }
                wordFirst = false;
                continue;
            } else {
                if (e <= 'Z') {
                    res += (e - 'A' + 'a');
                } else {
                    res += e;
                }
                first = false;
            }
        }
        if (res.size() > 100) {
            return res.substr(0, 100);
        }
        return res;
    }
};

int main() {
    string problemName = "3582";
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
        auto caption = jread_string(line_in);
        auto res = sol.generateTag(caption);
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