#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

int kth_element(vector<int>& nums, int i, int j, int k) {
    if (k == 0 || k == j - i + 1) {
        return 0;
    }
    srand(time(NULL));
    int l = i + 1;
    int r = j;
    int mid = rand() % (j - i + 1) + i;
    int p = nums[mid];
    nums[mid] = nums[i];
    while (true) {
        while (l <= r) {
            if (nums[l] > p) {
                swap(nums[l], nums[r]);
                --r;
            } else {
                ++l;
            }
        }
        nums[i] = nums[r];
        nums[r] = p;
        if (r == k) break;
        if (r < k) {
            i = r + 1;
        } else {
            j = r - 1;
        }
        l = i + 1;
        r = j;
        mid = rand() % (j - i + 1) + i;
        p = nums[mid];
        nums[mid] = nums[i];
    }
    return nums[k];
}

class Solution {
   public:
    int minimumCost(vector<int>& nums) {
        int n = nums.size();
        kth_element(nums, 1, n - 1, 2);
        return nums[0] + nums[1] + nums[2];
    }
};

int main() {
    string problemName = "3010";
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
        auto res = sol.minimumCost(nums);
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