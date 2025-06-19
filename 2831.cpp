#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 1e5;
const int LO = 1;
const int HI = N;
int fre[N + 1];
class Solution {
   public:
    int longestEqualSubarray(vector<int>& nums, int k) {
        int n = nums.size();
        int minV = HI + 1;
        int maxV = LO - 1;
        for (int i = 0; i < n; i++) {
            if (minV > nums[i]) {
                minV = nums[i];
            }
            if (maxV < nums[i]) {
                maxV = nums[i];
            }
        }
        for (int i = minV; i <= maxV; i++) {
            fre[i] = 0;
        }
        int maxFre = 0;
        int i = 0;
        for (int j = 0; j < n; j++) {
            fre[nums[j]]++;
            // lee's trick
            if (maxFre < fre[nums[j]]) {
                maxFre = fre[nums[j]];
            }
            if (j - i + 1 - maxFre > k) {
                fre[nums[i]]--;
                i++;
            }
        }
        return maxFre;
    }
};

int main() {
    string problemName = "2831";
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
        auto res = sol.longestEqualSubarray(nums, k);
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