#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int maxQ = INT32_MAX / 10;
const int maxR = INT32_MAX % 10;
const int minQ = INT32_MIN / 10;
const int minR = INT32_MIN % 10;
const int D = 10;
int digits[D];

class Solution {
   public:
    int reverse(int x) {
        bool isNeg = x < 0;
        int d = 0;
        while (x != 0) {
            int r = x % 10;
            if (r < 0) {
                r = -r;
            }
            digits[d++] = r;
            x /= 10;
        }
        int res = 0;
        if (isNeg) {
            for (int i = 0; i < d; i++) {
                if (minQ > res) {
                    return 0;
                } else if (minQ == res && minR > -digits[i]) {
                    return 0;
                }
                res = res * 10 - digits[i];
            }
        } else {
            for (int i = 0; i < d; i++) {
                if (maxQ < res) {
                    return 0;
                } else if (maxQ == res && maxR < digits[i]) {
                    return 0;
                }
                res = res * 10 + digits[i];
            }
        }
        return res;
    }
};

int main() {
    string problemName = "7";
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
        auto x = jread_int(line_in);
        auto res = sol.reverse(x);
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