#include "Jutil.h"
using namespace std;

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

int main() {
    vector<int> arr = {1, 8, 3, 4, 9, 2, 7, 6, 5};
    kth_element(arr, 0, 4, 2);
    jprint(arr, "arr");  // arr = [3,1,4,9,8,2,7,6,5]
    return 0;
}