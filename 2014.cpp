#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

// n/k <= 7
// 7!+C(7,6)*6!+C(7,5)*5!+...+C(7,1)*1! = 13699
const int STRMAX = 7;
const int C = 26;
const int Q = 13699;
struct Str {
    int c[STRMAX];
    int len;
};
int fre[C];
Str q[Q];
int charArr[STRMAX];

class Solution {
   public:
    string longestSubsequenceRepeatedK(string s, int k) {
        int n = s.size();
        for (int i = 0; i < C; i++) {
            fre[i] = 0;
        }
        for (int i = 0; i < n; i++) {
            fre[s[i] - 'a']++;
        }
        int a = 0;
        int l = 0;
        int r = 0;
        for (int i = C - 1; i >= 0; i--) {
            if (fre[i] >= k) {
                int c = i + 'a';
                q[r].c[0] = c;
                q[r].len = 1;
                r++;
                charArr[a++] = c;
            }
        }
        if (r == 0) {
            return "";
        }
        Str &best = q[l];
        while (l < r) {
            Str &f = q[l++];
            if (best.len < f.len) {
                best = f;
            }
            if (f.len == STRMAX) {
                break;
            }
            Str tmp;
            for (int i = 0; i < f.len; i++) {
                tmp.c[i] = f.c[i];
            }
            tmp.len = f.len + 1;
            for (int i = 0; i < a; i++) {
                tmp.c[f.len] = charArr[i];
                int x = 0;
                int y = 0;
                int cnt = 0;
                while (x < n) {
                    if (s[x] == tmp.c[y]) {
                        y++;
                        if (y == tmp.len) {
                            y = 0;
                            cnt++;
                            if (cnt >= k) {
                                q[r++] = tmp;
                                break;
                            }
                        }
                    }
                    x++;
                }
            }
        }
        string res(best.len, 0);
        for (int i = 0; i < best.len; i++) {
            res[i] = best.c[i];
        }
        return res;
    }
};

int main() {
    string problemName = "2014";
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
        auto res = sol.longestSubsequenceRepeatedK(s, k);
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