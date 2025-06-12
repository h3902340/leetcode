#include <_stdlib.h>

#include <fstream>

#include "Jutil.h"

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    int findClosest(int x, int y, int z) {
        int xDis = abs(x - z);
        int yDis = abs(y - z);
        if (xDis == yDis) {
            return 0;
        } else if (xDis < yDis) {
            return 1;
        }
        return 2;
    }
};

int main() {
    const string problemName = "3516";
    auto begin = jtimer();
    Solution sol;
    ifstream file_in("testcases/" + problemName + "_in.txt");
    ifstream file_out("testcases/" + problemName + "_out.txt");
    bool allPass = true;
    int caseCount = 0;
    int passCount = 0;
    string line_in1;
    string line_in2;
    string line_in3;
    string line_out;
    while (getline(file_in, line_in1)) {
        auto x = jread_int(line_in1);
        getline(file_in, line_in2);
        auto y = jread_int(line_in2);
        getline(file_in, line_in3);
        auto z = jread_int(line_in3);
        auto res = sol.findClosest(x, y, z);
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
        printf("x = %s\n", line_in1.c_str());
        printf("y = %s\n", line_in2.c_str());
        printf("z = %s\n", line_in3.c_str());
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