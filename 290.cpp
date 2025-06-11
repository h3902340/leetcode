#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

unordered_map<char, string> pToWord;
unordered_map<string, char> wordToP;
class Solution {
   public:
    bool wordPattern(string pattern, string s) {
        int n = s.size();
        pToWord.clear();
        wordToP.clear();
        int i = 0;
        for (auto& c : pattern) {
            if (i == n + 1) {
                return false;
            }
            int len = 1;
            while (i + len < n && s[i + len] != ' ') {
                len++;
            }
            string sub = s.substr(i, len);
            if (pToWord.count(c)) {
                if (pToWord[c] != sub) {
                    return false;
                }
            } else {
                pToWord[c] = sub;
            }
            if (wordToP.count(sub)) {
                if (wordToP[sub] != c) {
                    return false;
                }
            } else {
                wordToP[sub] = c;
            }
            i += len + 1;
        }
        if (i != n + 1) {
            return false;
        }
        return true;
    }
};

int main() {
    string problemName = "290";
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
        auto pattern = jread_string(line_in);
        getline(file_in, line_in);
        auto s = jread_string(line_in);
        auto res = sol.wordPattern(pattern, s);
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