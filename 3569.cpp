#include <map>
#include <set>
#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

// TODO: Is update function O(N) in the worst case? Maybe use doubly linked
// list?
struct SegmentTree {
    int l;
    int r;
    int data;
    int max;
};
const int NMAX = 5e4;
const int LEAFMAX = 17;  // (ceil(log2(NMAX))+1
const int TREEMAX = 1 << LEAFMAX;
SegmentTree tree[TREEMAX];
const int NUMMAX = 1e5;
bool prime[NUMMAX + 1];
bool isInit = false;
static void init() {
    if (isInit) return;
    prime[1] = false;
    for (int i = 2; i <= NUMMAX; i++) {
        prime[i] = true;
    }
    int cap = sqrt(NUMMAX);
    for (int i = 2; i <= cap; i++) {
        if (prime[i]) {
            for (int j = i + i; j <= NUMMAX; j += i) {
                prime[j] = false;
            }
        }
    }
    isInit = true;
}

class Solution {
   public:
    vector<int> maximumCount(vector<int>& nums, vector<vector<int>>& queries) {
        init();
        int n = nums.size();
        int m = queries.size();
        int max = 0;
        for (auto e : nums) {
            if (max < e) {
                max = e;
            }
        }
        map<int, set<int>> indexes;
        int t = 0;
        for (int i = 0; i < n; i++) {
            int e = nums[i];
            if (prime[e]) {
                indexes[e].insert(i);
            }
        }
        int distinctPrimes = indexes.size();
        build(0, 0, n);
        for (auto& kp : indexes) {
            int l = *kp.second.begin();
            int r = *kp.second.rbegin();
            if (l != r) {
                update(0, l, r + 1, 1);
            }
        }
        vector<int> res(m);
        for (int i = 0; i < m; i++) {
            int key = queries[i][0];
            int val = queries[i][1];
            int pre = nums[key];
            if (pre != val) {
                if (prime[pre]) {
                    int l = *indexes[pre].begin();
                    int r = *indexes[pre].rbegin();
                    if (l != r) {
                        if (key == l) {
                            update(0, l, r + 1, -1);
                            indexes[pre].erase(key);
                            l = *indexes[pre].begin();
                            if (l != r) {
                                update(0, l, r + 1, 1);
                            }
                        } else if (key == r) {
                            update(0, l, r + 1, -1);
                            indexes[pre].erase(key);
                            r = *indexes[pre].rbegin();
                            if (l != r) {
                                update(0, l, r + 1, 1);
                            }
                        } else {
                            indexes[pre].erase(key);
                        }
                    } else {
                        distinctPrimes--;
                        indexes[pre].erase(key);
                    }
                }
                if (prime[val]) {
                    if (indexes[val].size() == 0) {
                        indexes[val].insert(key);
                        distinctPrimes++;
                    } else {
                        int l = *indexes[val].begin();
                        int r = *indexes[val].rbegin();
                        if (l != r) {
                            if (key < l) {
                                update(0, l, r + 1, -1);
                                update(0, key, r + 1, 1);
                            } else if (r < key) {
                                update(0, l, r + 1, -1);
                                update(0, l, key + 1, 1);
                            }
                            indexes[val].insert(key);
                        } else {
                            indexes[val].insert(key);
                            int l = *indexes[val].begin();
                            int r = *indexes[val].rbegin();
                            update(0, l, r + 1, 1);
                        }
                    }
                }
            }
            nums[key] = val;
            res[i] = tree[0].max + distinctPrimes;
        }
        return res;
    }

   private:
    void build(int index, int l, int r) {
        SegmentTree& node = tree[index];
        node.l = l;
        node.r = r;
        node.data = 0;
        node.max = 0;
        if (node.l + 1 == node.r) return;
        int mid = (l + r) >> 1;
        build(index * 2 + 1, l, mid);
        build(index * 2 + 2, mid, r);
    }
    void update(int index, int l, int r, int v) {
        SegmentTree& root = tree[index];
        if (l == root.l && r == root.r) {
            root.data += v;
            root.max += v;
            updateParent(index);
            return;
        }
        int mid = (root.l + root.r) >> 1;
        if (r <= mid) {
            update(index * 2 + 1, l, r, v);
        } else if (mid <= l) {
            update(index * 2 + 2, l, r, v);
        } else {
            update(index * 2 + 1, l, mid, v);
            update(index * 2 + 2, mid, r, v);
        }
    }
    void updateParent(int index) {
        if (index == 0) return;
        index = (index - 1) >> 1;
        int a = tree[index * 2 + 1].max;
        int b = tree[index * 2 + 2].max;
        tree[index].max = tree[index].data + max(a, b);
        updateParent(index);
    }
};

int main() {
    string problemName = "3569";
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
        auto queries = jread_vector2d(line_in);
        auto res = sol.maximumCount(nums, queries);
        getline(file_out, line_out);
        auto ans = jread_vector(line_out);
        printf("Case %d", ++caseCount);
        if (res == ans) {
            passCount++;
            printf(" %s(PASS)", KGRN);
        } else {
            printf(" %s(WRONG)", KRED);
            allPass = false;
        }
        printf("\n%s", KNRM);
        // jprint(res, "res");
        // jprint(ans, "ans");
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