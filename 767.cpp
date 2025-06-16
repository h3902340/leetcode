#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    string reorganizeString(string s) {
        int n = s.size();
        for (int i = 0; i < n; i++) {
            int j = i + 1;
            while (j < n && s[i] == s[j]) {
                j++;
            }
            if (j < n) {
                swap(s[i + 1], s[j]);
            }
        }
        // second pass is necessary, for example, "babaa", can't be correct
        // without the second pass
        for (int i = n - 1; i >= 0; i--) {
            int j = i - 1;
            while (j >= 0 && s[i] == s[j]) {
                j--;
            }
            if (j >= 0) {
                swap(s[i - 1], s[j]);
            }
        }
        if (s[0] == s[1]) {
            return "";
        }
        return s;
    }
};

int main() {
    string problemName = "767";
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
        auto res = sol.reorganizeString(s);
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