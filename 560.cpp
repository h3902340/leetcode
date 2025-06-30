#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int LO = -1e7;
const int HI = 1e7;
int freq[HI - LO + 1];

class Solution {
   public:
    int subarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        int min = nums[0];
        int max = nums[0];
        for (int i = 1; i < n; i++) {
            nums[i] += nums[i - 1];
            if (min > nums[i]) {
                min = nums[i];
            }
            if (max < nums[i]) {
                max = nums[i];
            }
        }
        for (int i = min; i <= max; i++) {
            freq[i - min] = 0;
        }
        for (int i = 0; i < n; i++) {
            freq[nums[i] - min]++;
        }

        int res = 0;
        if (k >= min && k <= max) {
            res += freq[k - min];
        }
        if (k == 0) {
            for (int i = min; i <= max; i++) {
                res += freq[i - min] * (freq[i - min] - 1) >> 1;
            }
        } else {
            for (int i = 0; i < n; i++) {
                int right = nums[i] + k;
                if (min <= right && right <= max) {
                    res += freq[right - min];
                }
                freq[nums[i] - min]--;
            }
        }
        return res;
    }
};

int main() {
    string problemName = "560";
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
        auto res = sol.subarraySum(nums, k);
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