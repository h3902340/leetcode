#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

int f1[26];
int f2[26];
class Solution {
   public:
    bool canBeEqual(string s1, string s2) {
        int n = s1.size();
        memset(f1, 0, sizeof(f1));
        memset(f2, 0, sizeof(f2));
        for (int i = 0; i < n; i += 2) {
            f1[s1[i] - 'a']++;
            f2[s2[i] - 'a']++;
        }
        for (int i = 0; i < 26; i++) {
            if (f1[i] != f2[i]) {
                return false;
            }
        }
        memset(f1, 0, sizeof(f1));
        memset(f2, 0, sizeof(f2));
        for (int i = 1; i < n; i += 2) {
            f1[s1[i] - 'a']++;
            f2[s2[i] - 'a']++;
        }
        for (int i = 0; i < 26; i++) {
            if (f1[i] != f2[i]) {
                return false;
            }
        }
        return true;
    }
};

int main() {
    string problemName = "2839";
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
        auto s1 = jread_string(line_in);
        getline(file_in, line_in);
        auto s2 = jread_string(line_in);
        auto res = sol.canBeEqual(s1, s2);
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