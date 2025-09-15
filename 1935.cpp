#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const char A = 'a';
const char SPACE = ' ';
const int C = 26;
bool broken[C];
class Solution {
   public:
    int canBeTypedWords(string text, string brokenLetters) {
        for (int i = 0; i < C; i++) {
            broken[i] = false;
        }
        for (auto& c : brokenLetters) {
            broken[c - A] = true;
        }
        int res = 0;
        bool isBroken = false;
        for (auto& c : text) {
            if (c == SPACE) {
                if (!isBroken) {
                    res++;
                }
                isBroken = false;
                continue;
            }
            if (isBroken) {
                continue;
            }
            if (broken[c - A]) {
                isBroken = true;
            }
        }
        if (!isBroken) {
            res++;
        }
        return res;
    }
};

int main() {
    string problemName = "1935";
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
        auto text = jread_string(line_in);
        getline(file_in, line_in);
        auto brokenLetters = jread_string(line_in);
        auto res = sol.canBeTypedWords(text, brokenLetters);
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