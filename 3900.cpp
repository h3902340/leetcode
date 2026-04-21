#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 1e5;
int a[N * 2 + 1][2];
int zero[N + 1];
int one[N + 1];
class Solution {
   public:
    int longestBalanced(string s) {
        int n = s.size();
        int cap = n * 2 + 1;
        for (int i = 0; i < cap; i++) {
            for (int j = 0; j < 2; j++) {
                a[i][j] = -2;
            }
        }
        zero[0] = 0;
        one[0] = 0;
        for (int i = 0; i < n; i++) {
            zero[i + 1] = zero[i];
            one[i + 1] = one[i];
            if (s[i] == '0') {
                zero[i + 1]++;
            } else {
                one[i + 1]++;
            }
        }
        a[n][0] = -1;
        int d = n;
        int res = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == '0') {
                d--;
            } else {
                d++;
            }
            if (a[d][0] != -2) {
                res = max(res, i - a[d][0]);
            }
            if (d + 2 < cap) {
                if (a[d + 2][0] != -2) {
                    if (one[n] > one[i + 1] - one[a[d + 2][0] + 1]) {
                        res = max(res, i - a[d + 2][0]);
                    }
                }
                if (a[d + 2][1] != -2) {
                    res = max(res, i - a[d + 2][1]);
                }
            }
            if (d - 2 >= 0) {
                if (a[d - 2][0] != -2) {
                    if (zero[n] > zero[i + 1] - zero[a[d - 2][0] + 1]) {
                        res = max(res, i - a[d - 2][0]);
                    }
                }
                if (a[d - 2][1] != -2) {
                    res = max(res, i - a[d - 2][1]);
                }
            }
            if (a[d][0] == -2) {
                a[d][0] = i;
            } else if (a[d][1] == -2) {
                a[d][1] = i;
            }
        }
        return res;
    }
};

int main() {
    string problemName = "3900";
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
        auto s = jread_string(line_in);
        auto res = sol.longestBalanced(s);
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