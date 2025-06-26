#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 1000;
int ones[N];

class Solution {
   public:
    int longestSubsequence(string s, int k) {
        int n = s.size();
        int a = 0;
        int res = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == '0') {
                res++;
            } else {
                ones[a++] = i;
            }
        }
        a--;
        int b = 0;
        while (a >= 0) {
            int shift = n - 1 - ones[a];
            if (shift > 30) {
                break;
            }
            b += (1 << shift);
            if (b <= k) {
                res++;
                a--;
            } else {
                break;
            }
        }
        return res;
    }
};

int main() {
    string problemName = "2311";
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
        getline(file_in, line_in);
        auto k = jread_int(line_in);
        auto res = sol.longestSubsequence(s, k);
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