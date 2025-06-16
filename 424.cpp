#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

// using lee's sliding window technique (remember the current best by moving i
// and j simultaneously)
const int C = 26;
int fre[C];

class Solution {
   public:
    int characterReplacement(string s, int k) {
        int n = s.size();
        for (int i = 0; i < C; i++) {
            fre[i] = 0;
        }
        int maxFre = 0;
        int i = 0;
        for (int j = 0; j < n; j++) {
            char c = s[j] - 'A';
            fre[c]++;
            maxFre = max(maxFre, fre[c]);
            if (j - i + 1 - maxFre > k) {
                fre[s[i] - 'A']--;
                i++;
            }
        }
        return n - i;
    }
};

int main() {
    string problemName = "424";
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
        auto res = sol.characterReplacement(s, k);
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