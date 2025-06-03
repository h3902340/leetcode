#include <set>
#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

// TODO: The time complexity is still O(NX) because finding a element in a
// multiset requires O(X) time.
const int N = 1e5;
const int K = 15;
long long op[N];
long long dp[N][K + 1];
int tmp[N];

class Solution {
   public:
    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            tmp[i] = nums[i];
        }
        int xhalf = x >> 1;
        int med = kth_element(nums, 0, x - 1, xhalf);
        multiset<int> leftSet;
        multiset<int> rightSet;
        long long leftSum = 0;
        long long rightSum = 0;
        for (int i = 0; i < xhalf; i++) {
            leftSet.insert(nums[i]);
            leftSum += nums[i];
        }
        for (int i = xhalf; i < x; i++) {
            rightSet.insert(nums[i]);
            rightSum += nums[i];
        }
        for (int i = 0; i < n - x + 1; i++) {
            op[i] = (long long)med * xhalf - leftSum + rightSum -
                    (long long)med * (x - xhalf);
            if (i == n - x) break;
            int e = tmp[i];
            if (e < med) {
                auto itr = leftSet.find(e);
                if (itr != leftSet.end()) {
                    leftSet.erase(itr);
                }
                leftSum -= e;
            } else {
                auto itr = rightSet.find(e);
                if (itr != rightSet.end()) {
                    rightSet.erase(itr);
                }
                rightSum -= e;
            }
            int f = tmp[i + x];
            if (f < med) {
                leftSet.insert(f);
                leftSum += f;
            } else {
                rightSet.insert(f);
                rightSum += f;
            }
            if (leftSet.size() > xhalf) {
                int v = *prev(leftSet.end());
                rightSet.insert(v);
                leftSet.erase(prev(leftSet.end()));
                leftSum -= v;
                rightSum += v;
            } else if (leftSet.size() < xhalf) {
                int v = *rightSet.begin();
                leftSet.insert(v);
                rightSet.erase(rightSet.begin());
                leftSum += v;
                rightSum -= v;
            }
            med = *rightSet.begin();
        }
        for (int i = 0; i < n; i++) {
            dp[i][0] = 0;
        }
        long long min = op[n - x];
        dp[n - x][1] = min;
        for (int i = n - x - 1; i >= 0; i--) {
            if (min > op[i]) {
                min = op[i];
            }
            dp[i][1] = min;
        }
        for (int j = 2; j <= k; j++) {
            int i = n - x * j;
            dp[i][j] = op[i] + dp[i + x][j - 1];
            min = dp[i][j];
            i--;
            for (; i >= 0; i--) {
                long long a = op[i] + dp[i + x][j - 1];
                if (min > a) {
                    min = a;
                }
                dp[i][j] = min;
            }
        }
        return dp[0][k];
    }

   private:
    int kth_element(vector<int>& nums, int i, int j, int k) {
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
};

int main() {
    string problemName = "3505";
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
        auto x = jread_int(line_in);
        getline(file_in, line_in);
        auto k = jread_int(line_in);
        auto res = sol.minOperations(nums, x, k);
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
        jprint_longlong(res, "res");
        jprint_longlong(ans, "ans");
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