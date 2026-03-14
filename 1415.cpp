#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    string getHappyString(int n, int k) {
        string res(n, 'a');
        int q = (k - 1) >> (n - 1);
        if (q > 2) {
            return "";
        }
        res[0] += q;
        k = k - (q << (n - 1)) - 1;
        for (int i = 1; i < n; i++) {
            bool a = (k & (1 << (n - 1 - i))) != 0;
            if (res[i - 1] == 'a') {
                res[i] = res[i - 1] + 1 + a;
            } else if (res[i - 1] == 'b') {
                res[i] = res[i - 1] + (a << 1) - 1;
            } else {
                res[i] = 'a' + a;
            }
        }
        return res;
    }
};

int main() {
    string problemName = "1415";
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
        getline(file_in, line_in);
        auto k = jread_int(line_in);
        auto res = sol.getHappyString(n, k);
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