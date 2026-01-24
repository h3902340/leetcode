#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int BIT = 9;
const int TOTAL_BIT = 18;
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

class Solution {
   public:
    int minPairSum(vector<int>& nums) {
        int n = nums.size();
        radixSort(nums, n);
        int res = nums[0] + nums[n - 1];
        int halfn = n >> 1;
        int j = n - 2;
        for (int i = 1; i < halfn; i++) {
            res = max(res, nums[i] + nums[j]);
            j--;
        }
        return res;
    }
};

int main() {
    string problemName = "1877";
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
        auto res = sol.minPairSum(nums);
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