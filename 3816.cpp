#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int C = 26;
const char a = 'a';
int rem[C];
int cnt[C];

class Solution {
   public:
    string lexSmallestAfterDeletion(string& s) {
        int n = s.size();
        for (int i = 0; i < C; i++) {
            rem[i] = 0;
            cnt[i] = 0;
        }
        for (int i = 0; i < n; i++) {
            rem[s[i] - a]++;
        }
        int j = 0;
        for (int i = 0; i < n; i++) {
            if (j > 0) {
                while (j > 0 && s[j - 1] > s[i]) {
                    int t = s[j - 1] - a;
                    if (rem[t] > 0) {
                        j--;
                        cnt[t]--;
                    } else if (cnt[t] > 1) {
                        j--;
                        cnt[t]--;
                    } else {
                        break;
                    }
                }
            }
            s[j++] = s[i];
            int x = s[i] - a;
            rem[x]--;
            cnt[x]++;
        }
        int last = s[j - 1] - a;
        while (cnt[last] > 1) {
            cnt[last]--;
            j--;
            last = s[j - 1] - a;
        }
        s.resize(j);
        return s;
    }
};

int main() {
    string problemName = "3816";
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
        auto res = sol.lexSmallestAfterDeletion(s);
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