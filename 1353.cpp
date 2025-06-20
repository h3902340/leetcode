#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    int maxEvents(vector<vector<int>>& events) {
        int n = events.size();
        auto cmp = [](vector<int>& a, vector<int>& b) { return a[0] < b[0]; };
        sort(events.begin(), events.end(), cmp);
        priority_queue<int, vector<int>, greater<int>> pq;
        int res = 0;
        int i = 0;
        int d = 1;
        while (i < n) {
            while (i < n && events[i][0] == d) {
                pq.push(events[i][1]);
                i++;
            }
            if (!pq.empty()) {
                pq.pop();
                res++;
            }
            if (i < n && pq.empty()) {
                d = events[i][0];
            } else {
                d++;
            }
            while (!pq.empty() && pq.top() < d) {
                pq.pop();
            }
        }
        while (true) {
            while (!pq.empty() && pq.top() < d) {
                pq.pop();
            }
            if (pq.empty()) break;
            pq.pop();
            res++;
            d++;
        }
        return res;
    }
};

int main() {
    string problemName = "1353";
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
        auto events = jread_vector2d(line_in);
        auto res = sol.maxEvents(events);
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