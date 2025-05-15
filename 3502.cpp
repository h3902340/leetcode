#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    vector<int> minCosts(vector<int> &cost) {
        int n = cost.size();
        int min = cost[0];
        for (int i = 1; i < n; i++) {
            if (cost[i] > min) {
                cost[i] = min;
            } else {
                min = cost[i];
            }
        }
        return cost;
    }
};

int main() {
    string problemNumber = "3502";
    auto begin = jtimer();
    Solution sol;
    ifstream file_in("testcases/" + problemNumber + "_in.txt");
    ifstream file_out("testcases/" + problemNumber + "_out.txt");
    bool allPass = true;
    int caseCount = 0;
    int passCount = 0;
    string line_in1;
    string line_out;
    while (getline(file_in, line_in1)) {
        auto cost = jread_vector(line_in1);
        auto res = sol.minCosts(cost);
        getline(file_out, line_out);
        auto ans = jread_vector(line_out);
        printf("Case %d", ++caseCount);
        if (res == ans) {
            passCount++;
            printf(" %s(PASS)", KGRN);
        } else {
            printf(" %s(WRONG)", KRED);
            allPass = false;
        }
        printf("\n%s", KNRM);
        printf("edges = %s\n", line_in1.c_str());
        jprint_vector(res, "res");
        jprint_vector(ans, "ans");
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