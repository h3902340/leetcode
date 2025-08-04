#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int U = 1e4;
int cnt[U + 1];

class Solution {
   public:
    int maximumUniqueSubarray(vector<int>& nums) {
        int n = nums.size();
        for (int i = 1; i <= U; i++) {
            cnt[i] = 0;
        }
        int i = 0;
        int dup = 0;
        int res = 0;
        int a = 0;
        for (int j = 0; j < n; j++) {
            if (cnt[nums[j]] == 1) {
                dup++;
            }
            cnt[nums[j]]++;
            a += nums[j];
            while (dup) {
                cnt[nums[i]]--;
                if (cnt[nums[i]] == 1) {
                    dup--;
                }
                a -= nums[i];
                i++;
            }
            res = max(res, a);
        }
        return res;
    }
};

int main() {
    string problemName = "1695";
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
        auto res = sol.maximumUniqueSubarray(nums);
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