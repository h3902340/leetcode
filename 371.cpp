#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Out {
    bool carryOut;
    bool res;
};
class Solution {
   public:
    int getSum(int a, int b) {
        bool c = 0;
        int res = 0;
        int mask = 1;
        while (mask != 0) {
            Out out = adder(a & mask, b & mask, c);
            c = out.carryOut;
            if (out.res) {
                res = res | mask;
            }
            mask <<= 1;
        }
        return res;
    }
    Out adder(bool a, bool b, bool c) {
        Out out;
        out.carryOut = (a & b) | (a & c) | (b & c);
        out.res = a ^ b ^ c;
        return out;
    }
};

int main() {
    string problemName = "371";
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
        auto a = jread_int(line_in);
        getline(file_in, line_in);
        auto b = jread_int(line_in);
        auto res = sol.getSum(a, b);
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
        jprint_int(res, "res");
        jprint_int(ans, "ans");
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