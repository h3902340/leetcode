#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int CMAX = 26;
const int N = 1e5;
int lastIndex[CMAX];
int st[N];

class Solution {
   public:
    string robotWithString(string s) {
        int n = s.size();
        for (int i = 0; i < CMAX; i++) {
            lastIndex[i] = -1;
        }
        string t(n, 0);
        int k = 0;
        for (int i = 0; i < n; i++) {
            int c = s[i] - 'a';
            lastIndex[c] = i;
        }
        int c = 0;
        for (; c < CMAX; c++) {
            if (lastIndex[c] != -1) {
                break;
            }
        }
        int r = -1;
        int i = 0;
        for (; i <= lastIndex[c]; i++) {
            int d = s[i] - 'a';
            if (d == c) {
                t[k++] = s[i];
            } else {
                st[++r] = d;
            }
        }
        c++;
        for (; c < CMAX; c++) {
            while (r >= 0 && st[r] <= c) {
                t[k++] = st[r--] + 'a';
            }
            for (; i <= lastIndex[c]; i++) {
                int d = s[i] - 'a';
                if (d == c) {
                    t[k++] = s[i];
                } else {
                    st[++r] = d;
                }
            }
        }
        return t;
    }
};

int main() {
    string problemName = "2434";
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
        auto res = sol.robotWithString(s);
        getline(file_out, line_out);
        auto ans = jread_string(line_out);
        printf("Case %d", ++caseCount);
        if (res == ans) {
            passCount++;
            printf(" %s(PASS)", KGRN);
        } else {
            printf(" %s(WRONG)", KRED);
            allPass = false;
        }
        printf("\n%s", KNRM);
        jprint_string(s, "s");
        jprint_string(res, "res");
        jprint_string(ans, "ans");
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