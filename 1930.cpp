#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int U = 26;
const char a = 'a';
int two[U];
int three[U];

class Solution {
   public:
    int countPalindromicSubsequence(string s) {
        int n = s.size();
        int one = 0;
        for (int i = 0; i < U; i++) {
            two[i] = 0;
            three[i] = 0;
        }
        one |= (1 << (s[0] - a));
        one |= (1 << (s[1] - a));
        two[s[0] - a] |= (1 << (s[1] - a));
        for (int i = 2; i < n; i++) {
            int c = s[i] - a;
            three[c] = two[c];
            for (int j = 0; j < U; j++) {
                if (one & (1 << j)) {
                    two[j] |= (1 << c);
                }
            }
            one |= (1 << c);
        }
        int res = 0;
        for (int i = 0; i < U; i++) {
            res += __builtin_popcount(three[i]);
        }
        return res;
    }
};

int main() {
    string problemName = "1930";
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
        auto res = sol.countPalindromicSubsequence(s);
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