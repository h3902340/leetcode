#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    int minDeletionSize(vector<string>& strs) {
        int n = strs.size();
        int m = strs[0].size();
        int res = 0;
        int pre = -1;
        for (int i = 0; i < m; i++) {
            bool satisfied = true;
            for (int j = 1; j < n; j++) {
                if (pre != -1) {
                    if (strs[j - 1][pre] == 0) {
                        continue;
                    }
                }
                if (strs[j][i] > strs[j - 1][i]) {
                    strs[j - 1][i] = 0;
                } else if (strs[j][i] < strs[j - 1][i]) {
                    res++;
                    satisfied = false;
                    break;
                }
            }
            if (satisfied) {
                if (pre == -1) {
                    pre = i;
                } else {
                    for (int j = 0; j < n; j++) {
                        if (strs[j][i] == 0) {
                            strs[j][pre] = 0;
                        }
                    }
                }
            }
        }
        return res;
    }
};

int main() {
    string problemName = "955";
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
        auto strs = jread_vector_string(line_in);
        auto res = sol.minDeletionSize(strs);
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