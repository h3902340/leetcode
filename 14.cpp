#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    string longestCommonPrefix(vector<string>& strs) {
        int m = strs.size();
        int i = 0;
        bool stop = false;
        while (!stop) {
            char c = 0;
            for (int j = 0; j < m; j++) {
                if (i >= strs[j].size()) {
                    stop = true;
                    break;
                }
                if (c == 0) {
                    c = strs[j][i];
                    continue;
                }
                if (c != strs[j][i]) {
                    stop = true;
                    break;
                }
            }
            if (!stop) {
                i++;
            }
        }
        if (i == 0) {
            return "";
        }
        return strs[0].substr(0, i);
    }
};

int main() {
    string problemName = "14";
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
        auto res = sol.longestCommonPrefix(strs);
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