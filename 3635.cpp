#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    int earliestFinishTime(vector<int>& landStartTime,
                           vector<int>& landDuration,
                           vector<int>& waterStartTime,
                           vector<int>& waterDuration) {
        int m = landStartTime.size();
        int n = waterStartTime.size();
        int landEndMin = INT32_MAX;
        for (int i = 0; i < m; i++) {
            int a = landStartTime[i] + landDuration[i];
            landEndMin = min(landEndMin, a);
        }
        int waterEndMin = INT32_MAX;
        int res = INT32_MAX;
        for (int i = 0; i < n; i++) {
            int b = waterStartTime[i] + waterDuration[i];
            waterEndMin = min(waterEndMin, b);
            if (landEndMin < waterStartTime[i]) {
                int a = waterStartTime[i] + waterDuration[i];
                res = min(res, a);
                continue;
            }
            int a = landEndMin + waterDuration[i];
            res = min(res, a);
        }
        for (int i = 0; i < m; i++) {
            if (waterEndMin < landStartTime[i]) {
                int a = landStartTime[i] + landDuration[i];
                res = min(res, a);
                continue;
            }
            int a = waterEndMin + landDuration[i];
            res = min(res, a);
        }
        return res;
    }
};

int main() {
    string problemName = "3635";
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
        auto landStartTime = jread_vector(line_in);
        getline(file_in, line_in);
        auto landDuration = jread_vector(line_in);
        getline(file_in, line_in);
        auto waterStartTime = jread_vector(line_in);
        getline(file_in, line_in);
        auto waterDuration = jread_vector(line_in);
        auto res = sol.earliestFinishTime(landStartTime, landDuration,
                                          waterStartTime, waterDuration);
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