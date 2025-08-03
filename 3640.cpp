#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
class Solution {
   public:
    long long maxSumTrionic(vector<int>& nums) {
        int n = nums.size();
        bool isInit = false;
        ll res = 0;
        int i = 0;
        while (i < n) {
            int l = i;
            int up = findUp(nums, i, n);
            if (up == 1) {
                i++;
                continue;
            }
            i = i + up - 1;
            int p = i;
            int down = findDown(nums, i, n);
            if (down == 1) {
                i++;
                continue;
            }
            i = i + down - 1;
            int q = i;
            int up2 = findUp(nums, i, n);
            if (up2 == 1) {
                i++;
                continue;
            }
            int r = i + up2 - 1;
            ll a = nums[p - 1] + nums[p];
            ll b = a;
            for (int j = p - 2; j >= l; j--) {
                b += nums[j];
                a = max(a, b);
            }
            ll c = a;
            a = nums[q] + nums[q + 1];
            b = a;
            for (int j = q + 2; j <= r; j++) {
                b += nums[j];
                a = max(a, b);
            }
            c += a;
            for (int j = p + 1; j < q; j++) {
                c += nums[j];
            }
            if (isInit) {
                res = max(res, c);
            } else {
                res = c;
                isInit = true;
            }
        }
        return res;
    }
    int findUp(vector<int>& nums, int i, int n) {
        int res = 1;
        int cur = nums[i];
        for (int j = i + 1; j < n; j++) {
            if (cur < nums[j]) {
                cur = nums[j];
                res++;
            } else {
                break;
            }
        }
        return res;
    }
    int findDown(vector<int>& nums, int i, int n) {
        int res = 1;
        int cur = nums[i];
        for (int j = i + 1; j < n; j++) {
            if (cur > nums[j]) {
                cur = nums[j];
                res++;
            } else {
                break;
            }
        }
        return res;
    }
};

int main() {
    string problemName = "3640";
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
        auto res = sol.maxSumTrionic(nums);
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