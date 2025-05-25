#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int NMAX = 1e5;
const int CHARMAX = 26;
int m[CHARMAX][CHARMAX];

class Solution {
   public:
    int longestPalindrome(vector<string>& words) {
        int n = words.size();
        memset(m, 0, sizeof(m));
        int res = 0;
        for (auto& w : words) {
            m[w[0] - 'a'][w[1] - 'a']++;
        }
        for (int i = 0; i < CHARMAX; i++) {
            for (int j = i + 1; j < CHARMAX; j++) {
                res += (min(m[i][j], m[j][i]) << 2);
            }
        }
        bool hasOdd = false;
        for (int i = 0; i < CHARMAX; i++) {
            res += ((m[i][i] >> 1) << 2);
            hasOdd |= (m[i][i] & 1);
        }
        return res + (hasOdd << 1);
    }
};

int main() {
    string problemName = "2131";
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
        auto words = jread_vector_string(line_in);
        auto res = sol.longestPalindrome(words);
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
        jprint_int(res, "res");
        jprint_int(ans, "ans");
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