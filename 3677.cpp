#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 50;
int d[N];

class Solution {
   public:
    int countBinaryPalindromes(long long n) {
        if (n == 0) {
            return 1;
        }
        if (n == 1) {
            return 2;
        }
        if (n == 2) {
            return 2;
        }
        if (n == 3) {
            return 3;
        }
        int si = 0;
        while (n > 0) {
            d[si++] = n & 1;
            n >>= 1;
        }
        int half = si >> 1;
        int res = (1 << (half + 1)) - 1;
        if ((si & 1) == 0) {
            res -= 1 << (half - 1);
        }
        int i = si - 2;
        int j = 4;
        while (si >= j) {
            if (d[i] == 1) {
                res += 1 << ((si - j + 1) >> 1);
            }
            i--;
            j += 2;
        }
        if (si & 1) {
            if (d[i] == 1) {
                res++;
            }
        }
        bool isPal = true;
        int isSymSmaller = -1;
        i = half;
        j = half;
        if ((si & 1) == 0) {
            j--;
        }
        while (j >= 0) {
            if (d[i] != d[j]) {
                if (isSymSmaller == -1) {
                    if (d[i] < d[j]) {
                        isSymSmaller = 1;
                    } else {
                        isSymSmaller = 0;
                    }
                }
                isPal = false;
                if (!isPal && isSymSmaller != -1) {
                    break;
                }
            }
            i++;
            j--;
        }
        if (isPal) {
            res++;
        } else {
            if (isSymSmaller) {
                res++;
            }
        }
        return res;
    }
};

int main() {
    string problemName = "3677";
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
        auto n = jread_longlong(line_in);
        auto res = sol.countBinaryPalindromes(n);
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