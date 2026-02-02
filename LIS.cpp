#include "Jutil.h"
using namespace std;

int lengthOfLIS(vector<int>& nums, int n) {
    if (n == 0) {
        return 0;
    }
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

int main() {
    vector<int> nums = {4, 1, 3, 0, 7, 5, 36, 83, 13, 2};
    int n = nums.size();
    int res = lengthOfLIS(nums, n);
    printf("res:%d\n", res);  // res:5
    return 0;
}