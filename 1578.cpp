#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    int minCost(string colors, vector<int>& neededTime) {
        int n = colors.size();
        char pre = 0;
        int biggest = 0;
        int sum = 0;
        int res = 0;
        for (int i = 0; i < n; i++) {
            if (colors[i] == pre) {
                sum += neededTime[i];
                if (biggest < neededTime[i]) {
                    biggest = neededTime[i];
                }
            } else {
                res += (sum - biggest);
                pre = colors[i];
                sum = neededTime[i];
                biggest = neededTime[i];
            }
        }
        res += (sum - biggest);
        return res;
    }
};

int main() {
    string problemName = "1578";
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
        auto colors = jread_string(line_in);
        getline(file_in, line_in);
        auto neededTime = jread_vector(line_in);
        auto res = sol.minCost(colors, neededTime);
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