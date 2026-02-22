#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    string maximumXor(string s, string t) {
        int n = s.size();
        string res(n, 0);
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            if (t[i] == '1') {
                cnt++;
            }
        }
        int cnt2 = 0;
        for (int i = 0; i < n; i++) {
            res[i] = s[i];
            if (s[i] == '0') {
                cnt2++;
            }
        }
        for (int i = 0; i < n; i++) {
            if (cnt == 0) {
                break;
            }
            if (s[i] == '0') {
                res[i] = '1';
                cnt--;
            }
        }
        for (int i = n - 1; i >= 0; i--) {
            if (cnt == 0) {
                break;
            }
            if (s[i] == '1') {
                res[i] = '0';
                cnt--;
            }
        }
        return res;
    }
};

int main() {
    string problemName = "3849";
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
        getline(file_in, line_in);
        auto t = jread_string(line_in);
        auto res = sol.maximumXor(s, t);
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