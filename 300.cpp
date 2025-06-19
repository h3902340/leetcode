#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        int i = 0;
        for (int j = 1; j < n; j++) {
            if (nums[i] < nums[j]) {
                i++;
                nums[i] = nums[j];
            } else if (nums[i] > nums[j]) {
                int l = 0;
                int r = i;
                int max = -1;
                while (l <= r) {
                    int mid = (l + r) >> 1;
                    if (nums[mid] > nums[j]) {
                        r = mid - 1;
                    } else if (nums[mid] == nums[j]) {
                        max = mid - 1;
                        break;
                    } else {
                        max = mid;
                        l = mid + 1;
                    }
                }
                nums[max + 1] = nums[j];
            }
        }
        return i + 1;
    }
};

int main() {
    string problemName = "300";
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
        auto res = sol.lengthOfLIS(nums);
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