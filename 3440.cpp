#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    int maxFreeTime(int eventTime, vector<int>& startTime,
                    vector<int>& endTime) {
        int n = startTime.size();
        int res = 0;
        int hole1 = 0;
        int hole2 = 0;
        for (int i = 0; i < n; i++) {
            int a = startTime[i] - (i == 0 ? 0 : endTime[i - 1]);
            int b = (i == n - 1 ? eventTime : startTime[i + 1]) - endTime[i];
            int c = endTime[i] - startTime[i];
            if (hole1 < c) {
                res = max(res, a + b);
            } else {
                res = max(res, a + b + c);
            }
            hole1 = max(hole1, a);
            int j = n - 1 - i;
            a = startTime[j] - (j == 0 ? 0 : endTime[j - 1]);
            b = (j == n - 1 ? eventTime : startTime[j + 1]) - endTime[j];
            c = endTime[j] - startTime[j];
            if (hole2 < c) {
                res = max(res, a + b);
            } else {
                res = max(res, a + b + c);
            }
            hole2 = max(hole2, b);
        }
        return res;
    }
};

int main() {
    string problemName = "3440";
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
        auto startTime = jread_vector(line_in);
        getline(file_in, line_in);
        auto endTime = jread_vector(line_in);
        auto res = sol.maxFreeTime(eventTime, startTime, endTime);
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