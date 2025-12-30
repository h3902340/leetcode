#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
class Solution {
   public:
    long long maximumSubsequenceCount(string text, string pattern) {
        int n = text.size();
        if (pattern[0] == pattern[1]) {
            int a = 0;
            for (int i = 0; i < n; i++) {
                if (text[i] == pattern[0]) {
                    a++;
                }
            }
            return (ll)a * (a + 1) >> 1;
        }
        ll res = 0;
        int a = 0;
        int b = 0;
        for (int i = 0; i < n; i++) {
            if (text[i] == pattern[0]) {
                a++;
            } else if (text[i] == pattern[1]) {
                res += a;
                b++;
            }
        }
        res += max(a, b);
        return res;
    }
};

int main() {
    string problemName = "2207";
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
        auto text = jread_string(line_in);
        getline(file_in, line_in);
        auto pattern = jread_string(line_in);
        auto res = sol.maximumSubsequenceCount(text, pattern);
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