#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int C = 26;
int fre[C];

class Solution {
   public:
    int maxDifference(string s) {
        for (int i = 0; i < C; i++) {
            fre[i] = 0;
        }
        for (auto e : s) {
            fre[e - 'a']++;
        }
        int evenMin = INT32_MAX;
        int oddMax = 0;
        for (int i = 0; i < C; i++) {
            if (fre[i] == 0) continue;
            if (fre[i] & 1) {
                if (oddMax < fre[i]) {
                    oddMax = fre[i];
                }
            } else {
                if (evenMin > fre[i]) {
                    evenMin = fre[i];
                }
            }
        }
        return oddMax - evenMin;
    }
};

int main() {
    string problemName = "3442";
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
        auto res = sol.maxDifference(s);
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