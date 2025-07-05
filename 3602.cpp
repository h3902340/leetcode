#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    string concatHex36(int n) {
        int n2 = n * n;
        int n3 = n2 * n;
        string res = "";
        while (n2 > 0) {
            int r = n2 % 16;
            res += intToBase(r);
            n2 /= 16;
        }
        reverse(res.begin(), res.end());
        string a = "";
        while (n3 > 0) {
            int r = n3 % 36;
            a += intToBase(r);
            n3 /= 36;
        }
        reverse(a.begin(), a.end());
        res += a;
        return res;
    }
    char intToBase(int r) {
        if (r < 10) {
            return r + '0';
        }
        return r - 10 + 'A';
    }
};

int main() {
    string problemName = "3602";
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
        auto n = jread_int(line_in);
        auto res = sol.concatHex36(n);
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