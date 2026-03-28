#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
public:
    string findTheString(vector<vector<int>>& lcp) {
        int n = lcp.size();
        string s(n, 0);
        char a = 'a';
        for (int i = 0; i < n; i++) {
            int j = i;
            for (; j < n; j++) {
                if (s[j] == 0) {
                    if (a > 'z') {
                        return "";
                    }
                    s[j] = a;
                    break;
                }
            }
            int t = j++;
            for (; j < n; j++) {
                if (s[j] == 0 && lcp[t][j] > 0) {
                    s[j] = s[t];
                }
            }
            a++;
        }
        for (int i = n - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                if (s[i] == s[j]) {
                    if (i + 1 >= n || j + 1 >= n) {
                        if (lcp[i][j] != 1) {
                            return "";
                        }
                    } else {
                        if (lcp[i][j] != 1 + lcp[i + 1][j + 1]) {
                            return "";
                        }
                    }
                } else {
                    if (lcp[i][j] != 0) {
                        return "";
                    }
                }
            }
        }
        return s;
    }
};

int main() {
    string problemName = "2573";
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
        auto lcp = jread_vector2d(line_in);
        auto res = sol.findTheString(lcp);
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