#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Node {
    int mask;
    int sum;
    int index;
};
const int NMAX = 16;
Node s[1 << NMAX];
bool memo[1 << NMAX];

class Solution {
   public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        int total = 0;
        for (int i = 0; i < n; i++) {
            total += nums[i];
        }
        if (total % k != 0) {
            return false;
        }
        for (int i = 0; i < (1 << n); i++) {
            memo[i] = false;
        }
        int target = total / k;
        int used = 1;
        int allUsed = (1 << n) - 1;
        int t = 0;
        s[t].mask = used;
        s[t].sum = nums[0];
        s[t].index = 0;
        while (t >= 0) {
            Node top = s[t--];
            if (memo[top.mask]) {
                continue;
            }
            memo[top.mask] = true;
            if (top.sum == target) {
                if (top.mask == allUsed) {
                    return true;
                }
                top.sum = 0;
                top.index = 0;
            }
            for (int i = top.index + 1; i < n; i++) {
                int m = 1 << i;
                if (top.mask & m) {
                    continue;
                }
                int sum = top.sum + nums[i];
                if (sum > target) {
                    break;
                }
                t++;
                s[t].mask = top.mask | m;
                s[t].sum = sum;
                s[t].index = i;
            }
        }
        return false;
    }
};

int main() {
    string problemName = "698";
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
        auto k = jread_int(line_in);
        auto res = sol.canPartitionKSubsets(nums, k);
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