#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    int fillCups(vector<int>& amount) {
        priority_queue<int> pq;
        for (auto e : amount) {
            if (e > 0) {
                pq.push(e);
            }
        }
        int res = 0;
        while (!pq.empty()) {
            int t = pq.top();
            pq.pop();
            if (!pq.empty()) {
                int t2 = pq.top();
                pq.pop();
                t2--;
                if (t2 > 0) {
                    pq.push(t2);
                }
            }
            t--;
            if (t > 0) {
                pq.push(t);
            }
            res++;
        }
        return res;
    }
};

int main() {
    string problemName = "2335";
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
        auto amount = jread_vector(line_in);
        auto res = sol.fillCups(amount);
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