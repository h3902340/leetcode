#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    int minOperations(string s) {
        int n = s.size();
        bool isSorted = true;
        char mn = s[0];
        char mx = s[0];
        int mnc = 1;
        int mxc = 1;
        for (int i = 1; i < n; i++) {
            if (s[i] < s[i - 1]) {
                isSorted = false;
            }
            if (mn > s[i]) {
                mn = s[i];
                mnc = 1;
            } else if (mn == s[i]) {
                mnc++;
            }
            if (mx < s[i]) {
                mx = s[i];
                mxc = 1;
            } else if (mx == s[i]) {
                mxc++;
            }
        }
        if (isSorted) {
            return 0;
        }
        if (n == 2) {
            return -1;
        }
        if (s[0] == mn || s[n - 1] == mx) {
            return 1;
        }
        if (s[0] == mx && s[n - 1] == mn && mxc == 1 && mnc == 1) {
            return 3;
        }
        return 2;
    }
};

int main() {
    string problemName = "3863";
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
        auto res = sol.minOperations(s);
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