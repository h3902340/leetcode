#include <string>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

// TODO: time is bad (60 ms)
class Solution {
   public:
    string smallestPalindrome(string s) {
        int n = s.size();
        int fre[26]{0};
        for (int i = 0; i < n; i++) {
            fre[s[i] - 'a']++;
        }
        string ans = "";
        int oddIndex = -1;
        for (int i = 0; i < 26; i++) {
            if (fre[i] & 1) {
                oddIndex = i;
            }
            for (int j = 0; j < fre[i] >> 1; j++) {
                ans += ('a' + i);
            }
        }
        if (oddIndex != -1) {
            ans += ('a' + oddIndex);
        }
        for (int i = (n >> 1) - 1; i >= 0; i--) {
            ans += ans[i];
        }
        return ans;
    }
};

int main() {
    const string problemName = "3517";
    auto begin = jtimer();
    Solution sol;
    ifstream file_in("testcases/" + problemName + "_in.txt");
    ifstream file_out("testcases/" + problemName + "_out.txt");
    bool allPass = true;
    int caseCount = 0;
    int passCount = 0;
    string line_in1;
    string line_out;
    while (getline(file_in, line_in1)) {
        auto s = jread_string(line_in1);
        auto res = sol.smallestPalindrome(s);
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
        printf("s = %s\n", line_in1.c_str());
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