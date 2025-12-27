#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 1e5;
int buffer[N];

class Solution {
   public:
    string reverseWords(string s) {
        int n = s.size();
        int cnt = 0;
        int i = 0;
        while (i < n) {
            if (s[i] == ' ') {
                break;
            }
            if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' ||
                s[i] == 'u') {
                cnt++;
            }
            i++;
        }
        i++;
        int c = 0;
        int j = i;
        int k = -1;
        for (; i < n; i++) {
            if (s[i] == ' ') {
                if (c == cnt) {
                    while (k >= 0) {
                        s[j++] = buffer[k--];
                    }
                    j++;
                } else {
                    k = -1;
                    j = i + 1;
                }
                c = 0;
            } else {
                if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' ||
                    s[i] == 'u') {
                    c++;
                }
                buffer[++k] = s[i];
            }
        }
        if (c == cnt) {
            while (k >= 0) {
                s[j++] = buffer[k--];
            }
        }
        return s;
    }
};

int main() {
    string problemName = "3775";
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
        auto res = sol.reverseWords(s);
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