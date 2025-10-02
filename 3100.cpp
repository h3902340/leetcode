#include <cmath>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    int maxBottlesDrunk(int numBottles, int numExchange) {
        // (numExchange*2+x-1)x/2=numBottles =>
        // numExchange*2x+x^2-x=numBottles*2 =>
        // x^2+(numExchange*2-1)x-numBottles*2=0
        // x=(-numExchange*2+1+sqrt(numExchange^2*4-numExchange*4+1+numBottles*8))/2
        int a = 1;
        int b = numExchange * 2 - 1;
        int c = -numBottles * 2;
        int x = (-b + sqrt((double)b * b - 4 * a * c)) / (2 * a);
        int r = numBottles - (numExchange * 2 + x - 1) * x / 2;
        if (r >= numExchange) {
            x++;
        }
        return numBottles + x;
    }
};

int main() {
    string problemName = "3100";
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
        auto numBottles = jread_int(line_in);
        getline(file_in, line_in);
        auto numExchange = jread_int(line_in);
        auto res = sol.maxBottlesDrunk(numBottles, numExchange);
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