#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int C = 26;
int cnt[C];
class Solution {
   public:
    int longestBalanced(string s) {
        int n = s.size();
        int res = 0;
        for (int i = 0; i < n; i += 2) {
            for (int j = i; j < n; j++) {
                cnt[s[j] - 'a']++;
                bool ok = true;
                int c = cnt[s[j] - 'a'];
                for (int k = 0; k < C; k++) {
                    if (cnt[k] > 0 && cnt[k] != c) {
                        ok = false;
                        break;
                    }
                }
                if (ok) {
                    int a = j - i + 1;
                    if (res < a) {
                        res = a;
                    }
                }
            }
            cnt[s[i] - 'a']--;
            for (int j = n - 1; j > i; j--) {
                bool ok = true;
                int c = cnt[s[j] - 'a'];
                for (int k = 0; k < C; k++) {
                    if (cnt[k] > 0 && cnt[k] != c) {
                        ok = false;
                        break;
                    }
                }
                if (ok) {
                    int a = j - i;
                    if (res < a) {
                        res = a;
                    }
                }
                cnt[s[j] - 'a']--;
            }
        }
        return res;
    }
};

int main() {
    string problemName = "3713";
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
        auto res = sol.longestBalanced(s);
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