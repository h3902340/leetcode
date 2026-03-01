#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int C = 26;
int mp[C];
class Solution {
   public:
    string mergeCharacters(string s, int k) {
        int n = s.size();
        int j = 1;
        int l = 0;
        for (int i = 0; i < C; i++) {
            mp[i] = -1;
        }
        mp[s[0] - 'a'] = 0;
        for (int i = 1; i < n; i++) {
            int c = s[i] - 'a';
            if (mp[c] != -1 && mp[c] + k >= i - l) {
                l++;
                continue;
            }
            s[j++] = s[i];
            mp[c] = i - l;
        }
        s.resize(j);
        return s;
    }
};

int main() {
    string problemName = "3853";
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
        auto res = sol.mergeCharacters(s, k);
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