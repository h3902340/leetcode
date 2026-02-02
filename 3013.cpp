#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
const int N = 1e5;
class FenwickTree {
    int sz;
    int hi;

   public:
    struct Data {
        int cnt;
        ll sum;
    };
    Data tree[N];
    void init(int n) {
        sz = n;
        hi = 1 << (31 - __builtin_clz(n - 1));
        for (int i = 1; i < sz; i++) {
            tree[i] = {0, 0};
        }
    }
    void add(int i, int c, int v) {
        while (i < sz) {
            tree[i].cnt += c;
            tree[i].sum += v;
            i += i & -i;
        }
    }
    Data query(int i) {
        Data s = {0, 0};
        while (i > 0) {
            s.cnt += tree[i].cnt;
            s.sum += tree[i].sum;
            i -= i & -i;
        }
        return s;
    }
    int find(int k) {
        int res = 0;
        int acc = 0;
        for (int i = hi; i > 0; i >>= 1) {
            int x = res | i;
            int y = acc + tree[x].cnt;
            if (x >= sz) {
                continue;
            }
            if (k < y) {
                continue;
            }
            res = x;
            if (k == y) {
                break;
            }
            acc = y;
        }
        return res;
    }
};
const int BIT = 8;
const int TOTAL_BIT = 32;
const int BUCKET_SIZE = 1 << BIT;
const int MASK = BUCKET_SIZE - 1;
int buckets[BUCKET_SIZE];
int buf[2][N];
void radixSort(int n) {
    bool p = 0;
    bool q = 1;
    for (int j = 0; j < TOTAL_BIT; j += BIT) {
        for (int i = 0; i < n; i++) {
            buckets[(buf[p][i] >> j) & MASK]++;
        }
        for (int i = 1; i < BUCKET_SIZE; i++) {
            buckets[i] += buckets[i - 1];
        }
        for (int i = n - 1; i >= 0; i--) {
            buf[q][--buckets[(buf[p][i] >> j) & MASK]] = buf[p][i];
        }
        fill(begin(buckets), end(buckets), 0);
        swap(p, q);
    }
}
FenwickTree tree;
class HashMap {
    int sz;
    int table[N << 1];
    int val[N << 1];

   public:
    void init(int n) {
        sz = n << 1;
        for (int i = 0; i < sz; i++) {
            table[i] = 0;
        }
    }
    void insert(int k, int v) {
        int key = k % sz;
        for (int i = 0; i < sz; i++) {
            if (table[key] == 0) {
                table[key] = k;
                val[key] = v;
                break;
            }
            if (table[key] == k) {
                break;
            }
            key++;
            if (key == sz) {
                key = 0;
            }
        }
    }
    int getVal(int k) {
        int key = k % sz;
        for (int i = 0; i < sz; i++) {
            if (table[key] == 0) {
                return 0;
            }
            if (table[key] == k) {
                return val[key];
            }
            key++;
            if (key == sz) {
                key = 0;
            }
        }
        return 0;
    }
};
HashMap mp;

class Solution {
   public:
    long long minimumCost(vector<int>& nums, int k, int dist) {
        int n = nums.size();
        for (int i = 1; i < n; i++) {
            buf[0][i - 1] = nums[i];
        }
        radixSort(n - 1);
        int j = 0;
        mp.init(n);
        mp.insert(buf[0][0], 1);
        for (int i = 1; i < n - 1; i++) {
            if (buf[0][j] == buf[0][i]) {
                continue;
            }
            buf[0][++j] = buf[0][i];
            mp.insert(buf[0][i], j + 1);
        }
        j++;
        tree.init(j + 1);
        for (int i = 1; i <= dist + 1; i++) {
            int idx = mp.getVal(nums[i]);
            tree.add(idx, 1, nums[i]);
        }
        ll res = getAns(k - 1);
        j = 1;
        for (int i = dist + 2; i < n; i++) {
            int idx = mp.getVal(nums[j]);
            tree.add(idx, -1, -nums[j]);
            idx = mp.getVal(nums[i]);
            tree.add(idx, 1, nums[i]);
            ll a = getAns(k - 1);
            if (res > a) {
                res = a;
            }
            j++;
        }
        return res + nums[0];
    }
    ll getAns(int k) {
        int idx = tree.find(k);
        FenwickTree::Data d = tree.query(idx);
        if (d.cnt < k) {
            d.sum += (ll)buf[0][idx] * (k - d.cnt);
        }
        return d.sum;
    }
};

int main() {
    string problemName = "3013";
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
        getline(file_in, line_in);
        auto dist = jread_int(line_in);
        auto res = sol.minimumCost(nums, k, dist);
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