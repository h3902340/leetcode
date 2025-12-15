#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int MOD = 1e9 + 7;
int add(int a, int b) {
    a += b;
    if (a >= MOD) {
        a -= MOD;
    }
    return a;
}

class Solution {
   public:
    int numberOfWays(string corridor) {
        int n = corridor.size();
        int cnt = 0;
        int res = 1;
        for (int i = 0; i < n; i++) {
            if (corridor[i] == 'S') {
                if (cnt == 2) {
                    cnt = 1;
                } else {
                    cnt++;
                }
                continue;
            }
            if (cnt == 2) {
                int b = 0;
                while (i < n && corridor[i] == 'P') {
                    b = add(b, res);
                    i++;
                }
                if (i == n) {
                    return res;
                }
                res = add(res, b);
                cnt = 1;
            }
        }
        if (cnt == 2) {
            return res;
        }
        return 0;
    }
};

int main() {
    string problemName = "2147";
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
        auto corridor = jread_string(line_in);
        auto res = sol.numberOfWays(corridor);
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