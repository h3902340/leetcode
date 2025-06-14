#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    int minMaxDifference(int num) {
        vector<int> dg;
        while (num > 0) {
            dg.push_back(num % 10);
            num /= 10;
        }
        int a = dg[dg.size() - 1];
        int min = 0;
        for (int i = dg.size() - 1; i >= 0; i--) {
            if (dg[i] == a) {
                min = min * 10;
            } else {
                min = min * 10 + dg[i];
            }
        }
        int i = dg.size() - 1;
        int max = 0;
        while (i >= 0 && dg[i] == 9) {
            max = max * 10 + 9;
            i--;
        }
        if (i == -1) {
            return max - min;
        }
        a = dg[i];
        for (; i >= 0; i--) {
            if (dg[i] == a) {
                max = max * 10 + 9;
            } else {
                max = max * 10 + dg[i];
            }
        }
        return max - min;
    }
};

int main() {
    string problemName = "2566";
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
        auto num = jread_int(line_in);
        auto res = sol.minMaxDifference(num);
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