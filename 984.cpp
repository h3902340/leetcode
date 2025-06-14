#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    string strWithout3a3b(int a, int b) {
        int i = 0;
        if (a < b) {
            return f(a, b, 'a', 'b');
        }
        return f(b, a, 'b', 'a');
    }
    string f(int a, int b, char x, char y) {
        int n = a + b;
        string res(n, 0);
        int q = b / (a + 1);
        int r = b % (a + 1);
        int i = 0;
        bool isX = false;
        while (i < n) {
            if (isX) {
                res[i++] = x;
            } else {
                if (r > 0) {
                    for (int j = 0; j <= q; j++) {
                        res[i++] = y;
                    }
                    r--;
                } else {
                    for (int j = 0; j < q; j++) {
                        res[i++] = y;
                    }
                }
            }
            isX = !isX;
        }
        return res;
    }
};

int main() {
    string problemName = "984";
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
        auto a = jread_int(line_in);
        getline(file_in, line_in);
        auto b = jread_int(line_in);
        auto res = sol.strWithout3a3b(a, b);
        getline(file_out, line_out);
        auto ans = jread_string(line_out);
        printf("Case %d", ++caseCount);
        // the question has multiple answers
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