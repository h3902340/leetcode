#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int BUCKET_SIZE = 256;
const int MASK = 255;
const int BIAS = 0x80000000;

class Solution {
   public:
    int longestConsecutive(vector<int> &nums) {
        int n = nums.size();
        if (n == 0) return 0;
        radixSort(nums, n);
        int res = 1;
        int len = 1;
        for (int i = 0; i < n; i++) {
            while (i + 1 < n && nums[i + 1] == nums[i]) {
                i++;
            }
            if (i == n - 1) break;
            if (nums[i] + 1 == nums[i + 1]) {
                len++;
            } else {
                if (res < len) {
                    res = len;
                }
                len = 1;
            }
        }
        if (res < len) {
            res = len;
        }
        return res;
    }
    void radixSort(vector<int> &nums, int n) {
        for (int i = 0; i < n; i++) {
            nums[i] ^= BIAS;
        }
        vector<int> buckets(BUCKET_SIZE);
        vector<int> temp(n);
        for (int j = 0; j < 32; j += 8) {
            for (auto &e : nums) {
                buckets[(e >> j) & MASK]++;
            }
            for (int i = 1; i < BUCKET_SIZE; i++) {
                buckets[i] += buckets[i - 1];
            }
            for (int i = n - 1; i >= 0; i--) {
                temp[--buckets[(nums[i] >> j) & MASK]] = nums[i];
            }
            fill(buckets.begin(), buckets.end(), 0);
            nums.swap(temp);
        }
        for (int i = 0; i < n; i++) {
            nums[i] ^= BIAS;
        }
    }
};

int main() {
    string problemName = "128";
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
        auto res = sol.longestConsecutive(nums);
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