#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    string addBinary(string a, string b) {
        if (a.size() < b.size()) {
            swap(a, b);
        }
        int i = a.size() - 1;
        int j = b.size() - 1;
        int c = 0;
        while (i >= 0 || j >= 0) {
            int s = (a[i] - '0') + c;
            if (j >= 0) {
                s += (b[j] - '0');
            }
            a[i] = (s & 1) + '0';
            c = s >> 1;
            i--;
            j--;
        }
        if (c == 0) {
            return a;
        }
        return '1' + a;
    }
};

int main() {
    string problemName = "67";
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
        auto a = jread_string(line_in);
        getline(file_in, line_in);
        auto b = jread_string(line_in);
        auto res = sol.addBinary(a, b);
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