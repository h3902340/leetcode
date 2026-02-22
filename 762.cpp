#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define lg2(x) (32 - __builtin_clz(x))
const int N = 1e6;
const int LGN = lg2(N);
const int P = 8;
int C[LGN][LGN];
bool isInit = false;
void init() {
    for (int i = 0; i < LGN; i++) {
        C[i][0] = 1;
        C[i][i] = 1;
        for (int j = 1; j < i; j++) {
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
        }
    }
}
int p[P] = {2, 3, 5, 7, 11, 13, 17, 19};
class Solution {
   public:
    int countPrimeSetBits(int left, int right) {
        if (!isInit) {
            init();
            isInit = true;
        }
        return f(right + 1) - f(left);
    }
    int f(int r) {
        int a = lg2(r) - 1;
        int res = 0;
        int s = 0;
        for (int i = a; i >= 0; i--) {
            if (r & (1 << i)) {
                for (int j = 0; j < P; j++) {
                    if (p[j] < s) {
                        continue;
                    }
                    if (p[j] - s > i) {
                        break;
                    }
                    res += C[i][p[j] - s];
                }
                s++;
            }
        }
        return res;
    }
};

int main() {
    string problemName = "762";
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
        auto left = jread_int(line_in);
        getline(file_in, line_in);
        auto right = jread_int(line_in);
        auto res = sol.countPrimeSetBits(left, right);
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