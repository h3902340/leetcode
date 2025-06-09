#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int NUM = 2e4;
int mp[NUM + 1];

class Solution {
   public:
    int subarraysWithKDistinct(vector<int>& nums, int k) {
        return atMostK(nums, k) - atMostK(nums, k - 1);
    }
    int atMostK(vector<int>& nums, int k) {
        int n = nums.size();
        int max = nums[0];
        for (int j = 0; j < n; j++) {
            if (max < nums[j]) {
                max = nums[j];
            }
        }
        for (int j = 1; j <= max; j++) {
            mp[j] = 0;
        }
        int i = 0;
        int res = 0;
        int keys = 0;
        for (int j = 0; j < n; j++) {
            if (mp[nums[j]] == 0) {
                keys++;
            }
            mp[nums[j]]++;
            while (keys > k) {
                mp[nums[i]]--;
                if (mp[nums[i]] == 0) {
                    keys--;
                }
                i++;
            }
            res += j - i + 1;
        }
        return res;
    }
};

int main() {
    string problemName = "992";
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
        auto res = sol.subarraysWithKDistinct(nums, k);
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
        jprint_int(res, "res");
        jprint_int(ans, "ans");
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