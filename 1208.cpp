#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 1e5;
int diff[N];
class Solution {
   public:
    int equalSubstring(string s, string t, int maxCost) {
        int n = s.size();
        for (int i = 0; i < n; i++) {
            diff[i] = abs(s[i] - t[i]);
        }
        int res = 0;
        int c = 0;
        int i = 0;
        for (int j = 0; j < n; j++) {
            c += diff[j];
            // lee's trick
            if (c > maxCost) {
                c -= diff[i];
                i++;
            }
        }
        return n - i;
    }
};

int main() {
    string problemName = "1208";
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
        auto t = jread_string(line_in);
        getline(file_in, line_in);
        auto maxCost = jread_int(line_in);
        auto res = sol.equalSubstring(s, t, maxCost);
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