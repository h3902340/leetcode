#include <queue>
#include <set>
#include <unordered_set>
#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
struct Data {
    ll v;
    int i;
    bool operator<(const Data& rhs) const {
        return v == rhs.v ? i < rhs.i : v < rhs.v;
    }
};
const int N = 1e5;
Data heap[N << 1];
int idx;
int l[N];
int r[N];
ll s[N];
const int top = 1;
void push(Data a) {
    int i = idx++;
    while (i > top) {
        int p = i >> 1;
        if (heap[p] < a) {
            break;
        }
        heap[i] = heap[p];
        i = p;
    }
    heap[i] = a;
}
void heapify(int i) {
    Data a = heap[i];
    int l = i << 1;
    int r = l + 1;
    while (l < idx) {
        if (r < idx && heap[r] < heap[l]) {
            l = r;
        }
        if (a < heap[l]) {
            break;
        }
        heap[i] = heap[l];
        i = l;
        l = i << 1;
        r = l + 1;
    }
    heap[i] = a;
}
void pop() {
    heap[top] = heap[--idx];
    heapify(top);
}
void init(vector<int>& nums, int n, int& bad) {
    l[0] = -1;
    r[0] = 1;
    s[0] = nums[0];
    for (int i = 1; i < n; i++) {
        heap[i] = {nums[i - 1] + nums[i], i - 1};
        l[i] = i - 1;
        r[i] = i + 1;
        s[i] = nums[i];
        if (nums[i - 1] > nums[i]) {
            bad++;
        }
    }
    idx = n;
    int p = n >> 1;
    for (int i = p; i >= top; i--) {
        heapify(i);
    }
}

class Solution {
   public:
    int minimumPairRemoval(vector<int>& nums) {
        int n = nums.size();
        int bad = 0;
        init(nums, n, bad);
        int res = 0;
        while (bad > 0) {
            Data t = heap[top];
            pop();
            int& right = r[t.i];
            if (right == n) {
                continue;
            }
            if (s[t.i] + s[right] != t.v) {
                continue;
            }
            res++;
            ll tmp = s[t.i];
            s[t.i] = t.v;
            int nxt = r[right];
            if (nxt < n) {
                push({s[t.i] + s[nxt], t.i});
                if (s[right] > s[nxt]) {
                    if (s[t.i] <= s[nxt]) {
                        bad--;
                    }
                } else {
                    if (s[t.i] > s[nxt]) {
                        bad++;
                    }
                }
                l[nxt] = t.i;
            }
            int pre = l[t.i];
            if (pre >= 0) {
                push({s[pre] + s[t.i], pre});
                if (s[pre] > tmp) {
                    if (s[pre] <= s[t.i]) {
                        bad--;
                    }
                } else {
                    if (s[pre] > s[t.i]) {
                        bad++;
                    }
                }
            }
            if (tmp > s[right]) {
                bad--;
            }
            r[right] = n;
            l[right] = -1;
            right = nxt;
        }
        return res;
    }
};

int main() {
    string problemName = "3510";
    auto begin = jtimer();
    Solution sol;
    ifstream file_in("testcases/" + problemName + "_in.txt");
    ifstream file_out("testcases/" + problemName + "_out.txt");
    bool allPass = true;
    int caseCount = 0;
    int passCount = 0;
    string line_in1;
    string line_out;
    while (getline(file_in, line_in1)) {
        auto nums = jread_vector(line_in1);
        auto res = sol.minimumPairRemoval(nums);
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