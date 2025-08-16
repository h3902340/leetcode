#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
const int BUCKET_SIZE = 256;
const int MASK = 255;
void radixSort(vector<int> &nums) {
    int n = nums.size();
    vector<int> buckets(BUCKET_SIZE);
    vector<int> temp(n);
    for (int j = 0; j < 32; j += 8) {
        for (int i = 0; i < n; i++) {
            buckets[(nums[i] >> j) & MASK]++;
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
}

class Solution {
   public:
    long long perfectPairs(vector<int> &nums) {
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            nums[i] = abs(nums[i]);
        }
        radixSort(nums);
        ll res = 0;
        int i = 0;
        for (int j = 1; j < n; j++) {
            int a = nums[i];
            int b = nums[j];
            while (b - a > a) {
                i++;
                a = nums[i];
            }
            res += j - i;
        }
        return res;
    }
};

int main() {
    string problemName = "3649";
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
        auto res = sol.perfectPairs(nums);
        getline(file_out, line_out);
        auto ans = jread_longlong(line_out);
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