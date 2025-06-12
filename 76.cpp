#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

int fre[123];
bool isGoal[123];
class Solution {
   public:
    string minWindow(string s, string t) {
        int m = s.size();
        int n = t.size();
        memset(fre, 0, sizeof(fre));
        memset(isGoal, false, sizeof(isGoal));
        int goal = 0;
        for (auto &e : t) {
            if (fre[e] == 0) {
                isGoal[e] = true;
                goal++;
            }
            fre[e]++;
        }
        int i = 0;
        int imin = 0;
        int lmin = -1;
        for (int j = 0; j < m; j++) {
            if (isGoal[s[j]]) {
                fre[s[j]]--;
                if (fre[s[j]] == 0) {
                    goal--;
                }
            }
            while (goal == 0) {
                if (isGoal[s[i]]) {
                    fre[s[i]]++;
                    if (fre[s[i]] > 0) {
                        goal = 1;
                        int len = j - i + 1;
                        if (lmin == -1 || lmin > len) {
                            imin = i;
                            lmin = len;
                        }
                    }
                }
                i++;
            }
        }
        if (lmin == -1) {
            return "";
        }
        return s.substr(imin, lmin);
    }
};

int main() {
    string problemName = "76";
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
        auto res = sol.minWindow(s, t);
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