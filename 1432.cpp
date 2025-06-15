#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int D = 9;
int digits[D];
class Solution {
   public:
    int maxDiff(int num) {
        int a = num;
        int d = 0;
        while (a > 0) {
            digits[d++] = a % 10;
            a /= 10;
        }
        int res = 0;
        for (int i = d - 1; i >= 0; i--) {
            if (digits[i] != 9) {
                int t = (9 - digits[i]) * fastPow(10, i);
                for (int j = i; j >= 0; j--) {
                    if (digits[j] == digits[i]) {
                        res += t;
                    }
                    t /= 10;
                }
                break;
            }
        }
        for (int i = d - 1; i >= 0; i--) {
            if (digits[i] != 1 && digits[i] != 0) {
                int t = fastPow(10, i);
                if (i == d - 1) {
                    t *= (digits[i] - 1);
                } else {
                    t *= digits[i];
                }
                for (int j = i; j >= 0; j--) {
                    if (digits[j] == digits[i]) {
                        res += t;
                    }
                    t /= 10;
                }
                break;
            }
        }
        return res;
    }
    int fastPow(int a, int b) { return fastPowInternal(a, b, 1); }
    int fastPowInternal(int a, int b, int v) {
        if (b == 0) return v;
        if (b & 1) {
            return fastPowInternal(a, b - 1, v * a);
        }
        return fastPowInternal(a * a, b >> 1, v);
    }
};

int main() {
    string problemName = "1432";
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
        auto num = jread_int(line_in);
        auto res = sol.maxDiff(num);
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