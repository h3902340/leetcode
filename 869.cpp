#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int D = 31;
const int SYMBOL = 10;
int cnt[D][SYMBOL];
bool isInit = false;
static void init() {
    for (int i = 0; i < D; i++) {
        for (int j = 0; j < SYMBOL; j++) {
            cnt[i][j] = 0;
        }
        int a = 1 << i;
        while (a > 0) {
            int r = a % SYMBOL;
            cnt[i][r]++;
            a /= SYMBOL;
        }
    }
    isInit = true;
}
int temp[SYMBOL];

class Solution {
   public:
    bool reorderedPowerOf2(int n) {
        if (!isInit) {
            init();
        }
        for (int j = 0; j < SYMBOL; j++) {
            temp[j] = 0;
        }
        while (n > 0) {
            int r = n % SYMBOL;
            temp[r]++;
            n /= SYMBOL;
        }
        for (int i = 0; i < D; i++) {
            bool isEqual = true;
            for (int j = 0; j < SYMBOL; j++) {
                if (cnt[i][j] != temp[j]) {
                    isEqual = false;
                    break;
                }
            }
            if (isEqual) {
                return true;
            }
        }
        return false;
    }
};

int main() {
    string problemName = "869";
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
        auto res = sol.reorderedPowerOf2(n);
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