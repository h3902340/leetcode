#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

// TODO: this is not done
class Solution {
   public:
    int maxTaskAssign(vector<int>& tasks, vector<int>& workers, int pills,
                      int strength) {
        return 0;
    }
};

int main() {
    string problemName = "2071";
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
    string line_in4;
    string line_out;
    while (getline(file_in, line_in1)) {
        auto tasks = jread_vector(line_in1);
        getline(file_in, line_in2);
        auto workers = jread_vector(line_in2);
        getline(file_in, line_in3);
        auto pills = jread_int(line_in3);
        getline(file_in, line_in4);
        auto strength = jread_int(line_in4);
        int res = sol.maxTaskAssign(tasks, workers, pills, strength);
        getline(file_out, line_out);
        int ans = jread_int(line_out);
        printf("Case %d", ++caseCount);
        if (res == ans) {
            passCount++;
            printf(" %s(PASS)", KGRN);
        } else {
            printf(" %s(WRONG)", KRED);
            allPass = false;
        }
        printf("\n%s", KNRM);
        printf("tasks = %s\n", line_in1.c_str());
        printf("workers = %s\n", line_in2.c_str());
        printf("pills = %s\n", line_in3.c_str());
        printf("strength = %s\n", line_in4.c_str());
        jprint_int(res, "res");
        jprint_int(ans, "ans");
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