#include <map>
#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
const int BUCKET_SIZE = 64;
const int MASK = 63;
int buckets[BUCKET_SIZE];
const int N = 1e5;
ll prefix[N];
class Solution {
   public:
    int maxFrequency(vector<int>& nums, int k) {
        int n = nums.size();
        radixSort(nums);
        int i = 0;
        ll sum = 0;
        for (int j = 0; j < n; j++) {
            // lee's trick
            ll diff = (ll)(j - i) * nums[j] - sum;
            if (diff > k) {
                sum -= nums[i];
                i++;
            }
            sum += nums[j];
        }
        return n - i;
    }
    void radixSort(vector<int>& nums) {
        int n = nums.size();
        vector<int> temp(n);
        int max = BUCKET_SIZE - 1;
        for (int j = 0; j < 18; j += 6) {
            for (int i = 0; i <= max; i++) {
                buckets[i] = 0;
            }
            for (auto& e : nums) {
                int index = (e >> j) & MASK;
                buckets[index]++;
                if (max < index) {
                    max = index;
                }
            }
            for (int i = 1; i <= max; i++) {
                buckets[i] += buckets[i - 1];
            }
            for (int i = n - 1; i >= 0; i--) {
                temp[--buckets[(nums[i] >> j) & MASK]] = nums[i];
            }
            nums.swap(temp);
        }
    }
};

int main() {
    string problemName = "1838";
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
        auto res = sol.maxFrequency(nums, k);
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