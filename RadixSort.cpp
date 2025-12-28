#include "Jutil.h"
using namespace std;

const int BIT = 8;
const int TOTAL_BIT = 32;
const int BUCKET_SIZE = 1 << BIT;
const int MASK = BUCKET_SIZE - 1;
int buckets[BUCKET_SIZE];
void radixSort(vector<int>& nums, int n) {
    vector<int> temp(n);
    for (int j = 0; j < TOTAL_BIT; j += BIT) {
        for (int i = 0; i < n; i++) {
            buckets[(nums[i] >> j) & MASK]++;
        }
        for (int i = 1; i < BUCKET_SIZE; i++) {
            buckets[i] += buckets[i - 1];
        }
        for (int i = n - 1; i >= 0; i--) {
            temp[--buckets[(nums[i] >> j) & MASK]] = nums[i];
        }
        fill(begin(buckets), end(buckets), 0);
        swap(nums, temp);
    }
}

int main() {
    vector<int> nums = {3, 1, 4, 2};
    int n = nums.size();
    radixSort(nums, n);
    jprint(nums, "nums");  // nums = [1,2,3,4]
    return 0;
}