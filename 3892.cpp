#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 5000;
const int K = 5000;
const int U = 1e5;
const int L = -1e5;
// DP O(NK)
class Solution {
    int dp[3][K + 1];

   public:
    int minOperations(vector<int>& nums, int k) {
        int n = nums.size();
        if (k == 0) {
            return 0;
        }
        if (k > n / 2) {
            return -1;
        }
        int x = f(0, n - 1, nums, n, k);
        int y = f(1, n, nums, n, k);
        return min(x, y);
    }
    int f(int l, int r, vector<int>& nums, int n, int k) {
        for (int i = 0; i < 3; i++) {
            dp[i][0] = 0;
            for (int j = 1; j <= k; j++) {
                dp[i][j] = -1;
            }
        }
        int x = 0;
        int y = 1;
        int z = 2;
        for (int i = l; i < r; i++) {
            int c = max(nums[(i - 1 + n) % n], nums[(i + 1) % n]);
            int a = 0;
            if (nums[i] <= c) {
                a = a + c - nums[i] + 1;
            }
            for (int j = 1; j <= k; j++) {
                if (dp[z][j - 1] != -1) {
                    dp[x][j] = dp[z][j - 1] + a;
                }
                if (dp[y][j] != -1) {
                    dp[x][j] = min(dp[x][j], dp[y][j]);
                }
            }
            int t = z;
            z = y;
            y = x;
            x = t;
        }
        return dp[y][k];
    }
};

// alien trick O(Nlog(U-L))
class Solution2 {
    struct Data {
        int v;
        int c;
        bool operator<(const Data& a) const { return v < a.v; }
        bool operator>(const Data& a) const { return v > a.v; }
        Data& operator=(const Data& a) {
            v = a.v;
            c = a.c;
            return *this;
        }
    };
    int cost[N];

   public:
    int minOperations(vector<int>& nums, int k) {
        int n = nums.size();
        if (k == 0) {
            return 0;
        }
        if (k > n / 2) {
            return -1;
        }
        int c = 0;
        for (int i = 0; i < n; i++) {
            int l = i == 0 ? n - 1 : i - 1;
            int r = i == n - 1 ? 0 : i + 1;
            if (nums[i] > nums[l] && nums[i] > nums[r]) {
                c++;
            }
            cost[i] = max(0, max(nums[l], nums[r]) + 1 - nums[i]);
        }
        if (c >= k) {
            return 0;
        }
        int a1 = f(0, n - 1, false, n, k);
        int a2 = f(0, n - 1, true, n, k);
        int a3 = f(1, n, false, n, k);
        int a4 = f(1, n, true, n, k);
        return min({a1, a2, a3, a4});
    }
    int f(int s, int t, bool endPeak, int n, int k) {
        int l = 0;
        int r = 2e5 + 1;  // larger than largest possible cost
        while (l <= r) {
            int mid = (l + r) >> 1;
            Data a = {0, 0};  // not peak
            Data b = {0, 0};  // peak
            for (int i = s; i < t; i++) {
                int c = cost[i];
                if (c == 0) {
                    Data a2 = {b.v, b.c};
                    Data b2 = {a.v - mid, a.c + 1};
                    a = a2;
                    b = b2;
                } else {
                    Data a2 = a.v < b.v ? a : b;
                    Data b2 = {a.v + c - mid, a.c + 1};
                    a = a2;
                    b = b2;
                }
            }
            bool less = false;
            if (endPeak) {
                if (b.c == k) {
                    return b.v + b.c * mid;
                } else {
                    less = b.c < k;
                }
            } else {
                if (a.c == k) {
                    return a.v + a.c * mid;
                } else {
                    less = a.c < k;
                }
            }
            if (less) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        return INT32_MAX;
    }
};

// Greedy with undo O(N+KlogN)
class Solution3 {
    struct Data {
        int v;
        int i;
        bool operator<(const Data& a) const {
            return v == a.v ? i < a.i : v < a.v;
        }
        bool operator>(const Data& a) const {
            return v == a.v ? i > a.i : v > a.v;
        }
        Data& operator=(const Data& a) {
            v = a.v;
            i = a.i;
            return *this;
        }
    };
    int pre[N];
    int nxt[N];
    bool dead[N];
    Data cost[N];

   public:
    int minOperations(vector<int>& nums, int k) {
        int n = nums.size();
        if (k == 0) {
            return 0;
        }
        if (k > n / 2) {
            return -1;
        }
        for (int i = 0; i < n; i++) {
            pre[i] = i - 1;
            nxt[i] = i + 1;
            dead[i] = false;
        }
        pre[0] = n - 1;
        nxt[n - 1] = 0;
        for (int i = 0; i < n; i++) {
            int l = i == 0 ? n - 1 : i - 1;
            int r = i == n - 1 ? 0 : i + 1;
            int c = max(nums[l], nums[r]) + 1;
            int v = max(0, c - nums[i]);
            cost[i] = {v, i};
        }
        priority_queue<Data, vector<Data>, greater<Data>> pq(begin(cost),
                                                             begin(cost) + n);
        int res = 0;
        int cnt = 0;
        while (cnt < k) {
            Data u = pq.top();
            pq.pop();
            if (dead[u.i]) {
                continue;
            }
            res += u.v;
            int l = pre[u.i];
            int r = nxt[u.i];
            dead[l] = true;
            dead[r] = true;
            int v = cost[l].v + cost[r].v - cost[u.i].v;
            cost[u.i].v = v;
            pq.push({v, u.i});
            nxt[pre[l]] = u.i;
            pre[nxt[r]] = u.i;
            pre[u.i] = pre[l];
            nxt[u.i] = nxt[r];
            cnt++;
        }
        return res;
    }
};

// Greedy with undo and monotonic stack O(N)
class Solution4 {
    int cost[N];
    int st[N];
    int can[N];

   public:
    int minOperations(vector<int>& nums, int k) {
        int n = nums.size();
        if (k == 0) {
            return 0;
        }
        if (k > n / 2) {
            return -1;
        }
        for (int i = 0; i < n; i++) {
            int x = i == 0 ? n - 1 : i - 1;
            int y = i == n - 1 ? 0 : i + 1;
            cost[i] = max(0, max(nums[x], nums[y]) + 1 - nums[i]);
        }
        int a1 = f(0, n - 1, n, k);
        int a2 = f(1, n, n, k);
        return min(a1, a2);
    }
    int f(int l, int r, int n, int k) {
        int j = -1;
        int x = 0;
        for (int i = l; i <= r; i++) {
            int c = i == r ? (U - L + 2) : cost[i];
            while (j >= 0 && st[j] <= c) {
                can[x++] = st[j];
                if (j == 0) {
                    c = U - L + 2;
                    j--;
                    break;
                }
                c += st[j - 1] - st[j];
                j -= 2;
            }
            st[++j] = c;
        }
        nth_element(begin(can), begin(can) + k - 1, begin(can) + x);
        int res = 0;
        for (int i = 0; i < k; i++) {
            res += can[i];
        }
        return res;
    }
};

int main() {
    string problemName = "3892";
    auto begin = jtimer();
    Solution4 sol;
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
        auto res = sol.minOperations(nums, k);
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