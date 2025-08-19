#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Data {
    int x;
    int h;
};
const int M = 80;
const int N = 80;
const int MN = M * N;
const int WIDTH = 8;
const int BUCKET_SIZE = 1 << WIDTH;
const int CAP = WIDTH << 1;
const int MASK = BUCKET_SIZE - 1;
int dp[MN];
vector<Data> flat(MN);
vector<Data> temp(MN);
vector<int> buckets(BUCKET_SIZE);
void radixSortReverse(vector<Data>& nums, int n) {
    for (int j = 0; j < CAP; j += WIDTH) {
        fill(buckets.begin(), buckets.end(), 0);
        for (int i = 0; i < n; i++) {
            buckets[(nums[i].h >> j) & MASK]++;
        }
        for (int i = BUCKET_SIZE - 1; i >= 1; i--) {
            buckets[i - 1] += buckets[i];
        }
        for (int i = n - 1; i >= 0; i--) {
            temp[--buckets[(nums[i].h >> j) & MASK]] = nums[i];
        }
        swap(nums, temp);
    }
}

class Solution {
   public:
    int minCost(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        int mn = m * n;
        int idx = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                dp[idx] = INT32_MAX;
                flat[idx] = {idx, grid[i][j]};
                idx++;
            }
        }
        radixSortReverse(flat, mn);
        dp[0] = 0;
        forward(grid, m, n);
        for (int l = 0; l < k; l++) {
            bool changed = false;
            int idx = 0;
            int h = flat[0].h;
            int c = dp[flat[0].x];
            for (int i = 1; i < mn; i++) {
                if (h > flat[i].h) {
                    for (int j = idx; j < i; j++) {
                        int x = flat[j].x;
                        if (dp[x] != c) {
                            dp[x] = c;
                            changed = true;
                        }
                    }
                    idx = i;
                    h = flat[i].h;
                }
                c = min(c, dp[flat[i].x]);
            }
            for (int j = idx; j < mn; j++) {
                int x = flat[j].x;
                if (dp[x] != c) {
                    dp[x] = c;
                    changed = true;
                }
            }
            if (!changed) {
                break;
            }
            forward(grid, m, n);
        }
        return dp[mn - 1];
    }
    void forward(vector<vector<int>>& grid, int m, int n) {
        int idx = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (idx == 0) {
                    idx++;
                    continue;
                }
                int best = INT32_MAX;
                if (i > 0) {
                    best = dp[idx - n];
                }
                if (j > 0) {
                    best = min(best, dp[idx - 1]);
                }
                int a = best + grid[i][j];
                if (dp[idx] > a) {
                    dp[idx] = a;
                }
                idx++;
            }
        }
    }
};

int main() {
    string problemName = "3651";
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
        auto grid = jread_vector2d(line_in);
        getline(file_in, line_in);
        auto k = jread_int(line_in);
        auto res = sol.minCost(grid, k);
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