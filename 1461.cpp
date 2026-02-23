#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    bool hasAllCodes(string s, int k) {
        int n = s.size();
        vector<bool> seen(1 << k);
        int cnt = 1 << k;
        for (int i = 0; i <= n - k; i++) {
            int v = 0;
            for (int j = 0; j < k; j++) {
                v = (v << 1) + s[i + j] - '0';
            }
            if (!seen[v]) {
                seen[v] = true;
                cnt--;
            }
        }
        return cnt == 0;
    }
};

int main() {
    string problemName = "1461";
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
        auto res = sol.hasAllCodes(s, k);
        getline(file_out, line_out);
        auto ans = jread_bool(line_out);
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