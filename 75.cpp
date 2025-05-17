#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    void sortColors(vector<int>& nums) {
        int n = nums.size();
        int i = -1;
        int j = n;
        for (int k = 0; k < j; k++) {
            switch (nums[k]) {
                case 0:
                    swap(nums[k], nums[++i]);
                    break;
                case 1:
                    continue;
                case 2:
                    j--;
                    while (j >= 0 && nums[j] == 2) {
                        j--;
                    }
                    if (j <= k) {
                        break;
                    }
                    swap(nums[k], nums[j]);
                    if (nums[k] == 0) {
                        swap(nums[k], nums[++i]);
                    }
                    break;
            }
        }
    }
};

int main() {
    string problemName = "75";
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
        sol.sortColors(nums);
        getline(file_out, line_out);
        auto ans = jread_vector(line_out);
        printf("Case %d", ++caseCount);
        if (nums == ans) {
            passCount++;
            printf(" %s(PASS)", KGRN);
        } else {
            printf(" %s(WRONG)", KRED);
            allPass = false;
        }
        printf("\n%s", KNRM);
        jprint_vector(nums, "res");
        jprint_vector(ans, "ans");
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