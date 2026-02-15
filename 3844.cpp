#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
public:
    int almostPalindromic(string s) {
        int n = s.size();
        int res = 0;
        for (int i = 0; i < n; i++) {
            int r = 1;
            while (true) {
                if (i - r >= 0 && i + r < n&&s[i - r] == s[i + r]) {
                    r++;
                } else {
                    int t = r;
                    while (i - t - 1 >= 0 && i + t < n &&
                           s[i - t - 1] == s[i + t]) {
                        t++;
                    }
                    while (i - r >= 0 && i + r + 1 < n &&
                           s[i - r] == s[i + r + 1]) {
                        r++;
                    }
                    r = max(r, t);
                    break;
                }
            }
            int l = r * 2 - 1;
            if (l==n) {
                l--;
            } else {
                l++;
            }
            res = max(res, l);

            r = 0;
            while (true) {
                if (i - r >= 0 && i + 1 + r < n&&s[i - r] == s[i + 1 + r]) {
                    r++;
                } else {
                    int t = r;
                    while (i - t - 1 >= 0 && i + 1 + t < n &&
                           s[i - t - 1] == s[i + 1 + t]) {
                        t++;
                    }
                    while (i - r >= 0 && i + 1 + r + 1 < n &&
                           s[i - r] == s[i + 1 + r + 1]) {
                        r++;
                    }
                    r = max(r, t);
                    break;
                }
            }
            l = r * 2;
            if (l==n) {
                l--;
            } else {
                l++;
            }
            res = max(res, l);
        }
        return res;
    }
};

int main() {
    string problemName = "3844";
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
        auto res = sol.almostPalindromic(s);
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