#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    int minRemovals(vector<int>& nums, int target) {
        int n = nums.size();
        unordered_map<int, int> pre;
        unordered_map<int, int> cur;
        pre[0] = n;
        cur[0] = n;
        for (int i = 0; i < n; i++) {
            for (auto& e : pre) {
                int a = e.first ^ nums[i];
                if (cur.count(a)) {
                    cur[a] = min(cur[a], e.second - 1);
                } else {
                    cur[a] = e.second - 1;
                }
            }
            pre = cur;
        }
        if (pre.count(target)) {
            return pre[target];
        }
        return -1;
    }
};

int main() {
    string problemName = "3877";
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
        auto nums = jread_vector(line_in);
        getline(file_in, line_in);
        auto target = jread_int(line_in);
        auto res = sol.minRemovals(nums, target);
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