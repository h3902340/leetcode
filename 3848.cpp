#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int D = 10;
bool isInit = false;
int fact[D];
void init() {
    fact[0] = 1;
    for (int i = 1; i < D; i++) {
        fact[i] = fact[i - 1] * i;
    }
}
int cnt[D];

class Solution {
   public:
    bool isDigitorialPermutation(int n) {
        if (!isInit) {
            init();
            isInit = true;
        }
        for (int i = 0; i < D; i++) {
            cnt[i] = 0;
        }
        int s = 0;
        int l = 0;
        while (n > 0) {
            int d = n % 10;
            cnt[d]++;
            s += fact[d];
            n /= 10;
            l++;
        }
        while (s > 0) {
            int d = s % 10;
            if (cnt[d] == 0) {
                return false;
            }
            cnt[d]--;
            s /= 10;
            l--;
        }
        return l == 0;
    }
};

int main() {
    string problemName = "3848";
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
        auto res = sol.isDigitorialPermutation(n);
        getline(file_out, line_out);
        auto ans = jread_bool(line_out);
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