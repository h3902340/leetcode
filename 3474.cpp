#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 1e4;
const int M = 500;
int failure[M];
bool isMatch[M];
bool avail[N + M - 1];
bool occur[N];
int near[N];
void buildFailure(string& pattern) {
    int m = pattern.size();
    failure[0] = 0;
    isMatch[0] = false;
    for (int i = 1; i < m; i++) {
        isMatch[i] = false;
        int j = failure[i - 1];
        while (true) {
            if (pattern[j] == pattern[i]) {
                failure[i] = j + 1;
                break;
            }
            if (j == 0) {
                failure[i] = 0;
                break;
            }
            j = failure[j - 1];
        }
    }
    int i = m - 1;
    while (failure[i] != 0) {
        isMatch[failure[i] - 1] = true;
        i = failure[i - 1];
    }
}
void KMP(string& s, string& pattern) {
    int n = s.size();
    int m = pattern.size();
    int k = 0;
    for (int i = 0; i < n - m + 1; i++) {
        occur[i] = false;
    }
    int pre = -1;
    for (int i = 0; i < n; i++) {
        while (true) {
            if (s[i] == pattern[k]) {
                k++;
                if (k == m) {
                    occur[i - k + 1] = true;
                    k = failure[k - 1];
                }
                break;
            }
            if (k == 0) {
                break;
            }
            k = failure[k - 1];
        }
    }
}

class Solution {
   public:
    string generateString(string str1, string str2) {
        int n = str1.size();
        int m = str2.size();
        for (int i = 0; i < n + m - 1; i++) {
            avail[i] = true;
        }
        buildFailure(str2);
        string s(n + m - 1, 'a');
        int pre = -1;
        int j = 0;
        for (int i = 0; i < n; i++) {
            if (str1[i] == 'F') {
                continue;
            }
            if (pre == -1 || i - pre >= m) {
                if (j < i) {
                    j = i;
                }
                for (int k = 0; k < m; k++) {
                    avail[j] = false;
                    s[j++] = str2[k];
                }
            } else {
                if (!isMatch[m - 1 - i + pre]) {
                    return "";
                }
                for (int k = m - i + pre; k < m; k++) {
                    avail[j] = false;
                    s[j++] = str2[k];
                }
            }
            pre = i;
        }
        KMP(s, str2);
        j = -1;
        for (int i = 0; i < m; i++) {
            if (avail[i]) {
                j = i;
            }
        }
        near[0] = j;
        for (int i = 1; i < n; i++) {
            if (avail[i + m - 1]) {
                j = i + m - 1;
            }
            if (j < i) {
                j = -1;
            }
            near[i] = j;
        }
        pre = -1;
        for (int i = 0; i < n; i++) {
            if (str1[i] == 'T') {
                continue;
            }
            if (occur[i]) {
                if (near[i] == -1) {
                    return "";
                }
                if (pre < i) {
                    s[near[i]] = 'b';
                }
                pre = near[i];
            }
        }
        return s;
    }
};

int main() {
    string problemName = "3474";
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
        auto str1 = jread_string(line_in);
        getline(file_in, line_in);
        auto str2 = jread_string(line_in);
        auto res = sol.generateString(str1, str2);
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