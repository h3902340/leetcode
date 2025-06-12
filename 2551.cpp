#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    long long putMarbles(vector<int> &weights, int k) {
        int n = weights.size();
        if (k == 1 || k == n) return 0;
        for (int i = 0; i < n - 1; ++i) {
            weights[i] += weights[i + 1];
        }
        weights.pop_back();
        --n;
        long long ans = 0;
        int j = n - 1;
        --k;
        if (k > n >> 1) {
            k = n - k;
        }
        kth_element(weights, 0, n - 1, k - 1);
        kth_element(weights, k, n - 1, n - k);
        for (int i = 0; i < k; ++i) {
            ans += weights[j--] - weights[i];
        }
        return ans;
    }

   private:
    void kth_element(vector<int> &nums, int i, int j, int k) {
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
    }
};

int main() {
    string problemName = "2551";
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
        auto weights = jread_vector(line_in);
        getline(file_in, line_in);
        auto k = jread_int(line_in);
        auto res = sol.putMarbles(weights, k);
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