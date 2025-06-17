#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int C = 4;
int fre[C];
class Solution {
   public:
    int balancedString(string s) {
        int n = s.size();
        int t = n >> 2;
        for (int i = 0; i < C; i++) {
            fre[i] = 0;
        }
        for (int i = 0; i < n; i++) {
            switch (s[i]) {
                case 'Q':
                    fre[0]++;
                    break;
                case 'W':
                    fre[1]++;
                    break;
                case 'E':
                    fre[2]++;
                    break;
                case 'R':
                    fre[3]++;
                    break;
            }
        }
        bool isOK = check(t);
        if (isOK) return 0;
        int res = n;
        int i = 0;
        for (int j = 0; j < n; j++) {
            switch (s[j]) {
                case 'Q':
                    fre[0]--;
                    break;
                case 'W':
                    fre[1]--;
                    break;
                case 'E':
                    fre[2]--;
                    break;
                case 'R':
                    fre[3]--;
                    break;
            }
            while (check(t)) {
                int len = j - i + 1;
                if (res > len) {
                    res = len;
                }
                switch (s[i]) {
                    case 'Q':
                        fre[0]++;
                        break;
                    case 'W':
                        fre[1]++;
                        break;
                    case 'E':
                        fre[2]++;
                        break;
                    case 'R':
                        fre[3]++;
                        break;
                }
                i++;
            }
        }
        return res;
    }
    bool check(int t) {
        bool isOK = true;
        for (int k = 0; k < 4; k++) {
            if (fre[k] > t) {
                isOK = false;
                break;
            }
        }
        return isOK;
    }
};

int main() {
    string problemName = "1234";
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
        auto res = sol.balancedString(s);
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