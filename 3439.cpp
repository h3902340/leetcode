#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    int maxFreeTime(int eventTime, int k, vector<int>& startTime,
                    vector<int>& endTime) {
        int n = startTime.size();
        int gap = startTime[0];
        int cnt = 0;
        if (k >= n) {
            for (int i = 0; i < n - 1; i++) {
                gap += startTime[i + 1] - endTime[i];
            }
            gap += eventTime - endTime[n - 1];
            return gap;
        } else {
            for (int i = 0; i < k; i++) {
                gap += startTime[i + 1] - endTime[i];
            }
        }
        int res = gap;
        gap -= startTime[0];
        for (int i = k; i < n - 1; i++) {
            gap += startTime[i + 1] - endTime[i];
            res = max(res, gap);
            gap -= (startTime[i + 1 - k] - endTime[i - k]);
        }
        gap += eventTime - endTime[n - 1];
        res = max(res, gap);
        return res;
    }
};

int main() {
    string problemName = "3439";
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
        auto eventTime = jread_int(line_in);
        getline(file_in, line_in);
        auto k = jread_int(line_in);
        getline(file_in, line_in);
        auto startTime = jread_vector(line_in);
        getline(file_in, line_in);
        auto endTime = jread_vector(line_in);
        auto res = sol.maxFreeTime(eventTime, k, startTime, endTime);
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