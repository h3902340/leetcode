#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    string lastSubstring(string s) {
        int n = s.size();
        int i = 0;
        int j = 1;
        int k = 0;
        while (j + k < n) {
            if (s[i + k] == s[j + k]) {
                k++;
                continue;
            }
            if (s[i + k] < s[j + k]) {
                // If j is only updated to j+1, the worst case will be O(n^2),
                // for example, "aaa...aab" where there are n-1 "a". i is the
                // current best, j is the potential rival. i is unrivaled in
                // (i,j). Because s[i..i+k] is equal to s[j..j+k], when i+k >=
                // j, s[j..i+k] is equal to s[i..i-j+i+k]. Again, if i-j+i+k >=
                // j, then s[j..i-j+i+k] is equal to s[i..2(i-j)+i+k]. Repeat
                // this process until we get c(i-j)+i+k < j where c is a
                // constant. The characters in s[j..i+k] all appear in s[i..j].
                // Because i is unrival in (i,j-1], the characters in (i,j-1]
                // are no greater than s[i]. The characters in (j,i+k] are also
                // no greater than s[j]. Therefore, s[j] is unrivaled in
                // (j,i+k]. j can choose max(j+1,i+k+1) as the next starting
                // point.
                int t = i;
                i = j;
                j = max(j + 1, t + k + 1);
            } else {
                j = j + k + 1;
            }
            k = 0;
        }
        return s.substr(i, n - i);
    }
};

int main() {
    string problemName = "1163";
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
        auto res = sol.lastSubstring(s);
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