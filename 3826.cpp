#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
const int N = 1000;
class CHT {
    struct Line {
        int a;
        ll b;
        int j;
        double x;
    };

    Line deque[N + 1];
    int l;
    int r;

   public:
    void init() {
        l = 0;
        r = 1;
        deque[0] = {0, 0, -1, INT32_MAX};
    }
    void push(int a, ll b, int j) {
        Line line = {a, b, j, INT32_MAX};
        double p1 = solve(deque[r - 1], line);
        if (size() > 1) {
            double p2 = solve(deque[r - 2], line);
            while (p1 < p2) {
                r--;
                p1 = solve(deque[r - 1], line);
                if (size() == 1) {
                    break;
                }
                p2 = solve(deque[r - 2], line);
            }
        }
        deque[r - 1].x = p1;
        deque[r++] = line;
    }
    int size() { return r - l; }
    int getJ(int x) {
        while (x > deque[l].x) {
            l++;
        }
        return deque[l].j;
    }

   private:
    double solve(Line& l1, Line& l2) {
        return (double)(l2.b - l1.b) / (l1.a - l2.a);
    }
};
ll dp[N];
int seg[N];
CHT cht;

class Solution {
   public:
    long long minPartitionScore(vector<int>& nums, int k) {
        int n = nums.size();
        for (int i = 1; i < n; i++) {
            nums[i] += nums[i - 1];
        }
        ll l = 0;
        ll r = (ll)nums[n - 1] * nums[n - 1] >> 1;
        while (l <= r) {
            ll mid = (l + r) >> 1;
            cht.init();
            for (int i = 0; i < n; i++) {
                int j = cht.getJ(nums[i]);
                int a = nums[i];
                dp[i] = mid;
                seg[i] = 1;
                if (j >= 0) {
                    a -= nums[j];
                    seg[i] += seg[j];
                    dp[i] += dp[j];
                }
                dp[i] += (ll)a * a;
                cht.push(-2 * nums[i], dp[i] + (ll)nums[i] * nums[i], i);
            }
            if (seg[n - 1] == k) {
                return (dp[n - 1] - k * mid + nums[n - 1]) >> 1;
            }
            if (seg[n - 1] < k) {
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        return 0;
    }
};

int main() {
    string problemName = "3826";
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
        auto res = sol.minPartitionScore(nums, k);
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