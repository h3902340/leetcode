#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    string makeLargestSpecial(string s) {
        int n = s.size();
        int d = 0;
        int j = -1;
        vector<string> tmp;
        for (int i = 0; i < n; i++) {
            if (s[i] == '0') {
                d--;
            } else {
                d++;
            }
            if (d == 0) {
                string a = makeLargestSpecial(s.substr(j + 2, i - j - 2));
                tmp.push_back('1' + a + '0');
                j = i;
            }
        }
        sort(begin(tmp), end(tmp));
        string res;
        for (int i = tmp.size() - 1; i >= 0; i--) {
            res += tmp[i];
        }
        return res;
    }
};

int main() {
    string problemName = "761";
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
        auto res = sol.makeLargestSpecial(s);
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