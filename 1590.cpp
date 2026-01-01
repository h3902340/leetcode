#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    int minSubarray(vector<int>& nums, int p) {
        int n = nums.size();
        int a = 0;
        for (int i = 0; i < n; i++) {
            a = (a + nums[i]) % p;
            nums[i] = a;
        }
        if (a == 0) {
            return 0;
        }
        unordered_map<int, int> mp;
        mp[0] = -1;
        int res = n;
        for (int i = 0; i < n; i++) {
            mp[nums[i]] = i;
            int r = nums[i] - a;
            if (r < 0) {
                r += p;
            }
            if (mp.count(r)) {
                res = min(res, i - mp[r]);
            }
        }
        if (res == n) {
            return -1;
        }
        return res;
    }
};

int main() {
    string problemName = "1590";
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
        auto p = jread_int(line_in);
        auto res = sol.minSubarray(nums, p);
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