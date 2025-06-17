#include <set>
#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

// TODO: optimize to O(n) based on lee's solution
#define ll long long
const int N = 1000;
ll arr[N];
class Solution {
   public:
    long long minCost(vector<int>& nums, int x) {
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            arr[i] = 0;
        }
        for (int i = 0; i < n; i++) {
            arr[i] += (ll)x * i;
            ll cur = nums[i];
            arr[0] += cur;
            for (int shift = 1; shift < n; shift++) {
                ll tmp = nums[(i - shift + n) % n];
                cur = min(cur, tmp);
                arr[shift] += cur;
            }
        }
        ll res = arr[0];
        for (int i = 1; i < n; i++) {
            if (res > arr[i]) {
                res = arr[i];
            }
        }
        return res;
    }
};

int main() {
    string problemName = "2735";
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
        auto x = jread_int(line_in);
        auto res = sol.minCost(nums, x);
        getline(file_out, line_out);
        auto ans = jread_longlong(line_out);
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