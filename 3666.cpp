#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    int minOperations(string s, int k) {
        int n = s.size();
        int a = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == '0') {
                a++;
            }
        }
        if (a == 0) {
            return 0;
        }
        if (k == n) {
            if (a == n) {
                return 1;
            }
            return -1;
        }
        int q = a / k;
        if (a % k == 0) {
            return q;
        }
        q++;
        int x = (n - a + n - k - 1) / (n - k);
        if (x % 2 == 0) {
            x++;
        }
        if (x < q) {
            if (q % 2 == 0) {
                x = q + 1;
            } else {
                x = q;
            }
        }
        int y = (a + n - k - 1) / (n - k);
        if (y % 2 == 1) {
            y++;
        }
        if (y < q) {
            if (q % 2 == 0) {
                y = q;
            } else {
                y = q + 1;
            }
        }
        if ((q * k - a) % 2 == 1) {
            if (k % 2 == 0) {
                return -1;
            }
            q++;
            if (q % 2 == 0) {
                return y;
            } else {
                return x;
            }
        }
        if (k % 2 == 0) {
            return min(x, y);
        }
        if (q % 2 == 0) {
            return y;
        }
        return x;
    }
};

int main() {
    string problemName = "3666";
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
        auto res = sol.minOperations(s, k);
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