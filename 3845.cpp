#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 4e4;
class Deque {
    int deque[N];
    int l;
    int r;

   public:
    void init() {
        l = 0;
        r = 0;
    }
    void push(int v) { deque[r++] = v; }
    int front() { return deque[l]; }
    int back() { return deque[r - 1]; }
    void pop_front() { l++; }
    void pop_back() { r--; }
    bool empty() { return l == r; }
};

Deque deque1;
Deque deque2;

const int C = 2;
const int K = 15;
class Trie {
    struct Node {
        int idx[C];
        int cnt[C];
    };
    Node arr[N * K];
    int idx;

   public:
    void init() {
        for (int i = 0; i < C; i++) {
            arr[0].idx[i] = 0;
            arr[0].cnt[i] = 0;
        }
        idx = 1;
    }
    void add(int s) {
        int id = 0;
        for (int i = 1 << (K - 1); i > 0; i >>= 1) {
            int c = (s & i) ? 1 : 0;
            if (arr[id].idx[c] == 0) {
                for (int j = 0; j < C; j++) {
                    arr[idx].idx[j] = 0;
                    arr[idx].cnt[j] = 0;
                }
                arr[id].idx[c] = idx++;
            }
            arr[id].cnt[c]++;
            id = arr[id].idx[c];
        }
    }
    void remove(int s) {
        int id = 0;
        for (int i = 1 << (K - 1); i > 0; i >>= 1) {
            int c = (s & i) ? 1 : 0;
            arr[id].cnt[c]--;
            id = arr[id].idx[c];
        }
    }
    int findMax(int s) {
        int id = 0;
        for (int i = 1 << (K - 1); i > 0; i >>= 1) {
            int c = (s & i) ? 0 : 1;
            if (arr[id].cnt[c] == 0) {
                s ^= (s & i);
                c ^= 1;
            } else {
                s |= i;
            }
            id = arr[id].idx[c];
        }
        return s;
    }
};
Trie t;

class Solution {
   public:
    int maxXor(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> prefix(n);
        prefix[0] = nums[0];
        for (int i = 1; i < n; i++) {
            prefix[i] = prefix[i - 1] ^ nums[i];
        }
        deque1.init();
        deque2.init();
        t.init();
        t.add(0);
        int j = 0;
        int res = 0;
        for (int i = 0; i < n; i++) {
            while (!deque1.empty() && deque1.back() < nums[i]) {
                deque1.pop_back();
            }
            deque1.push(nums[i]);
            while (!deque2.empty() && deque2.back() > nums[i]) {
                deque2.pop_back();
            }
            deque2.push(nums[i]);
            while (deque1.front() - deque2.front() > k) {
                if (nums[j] == deque1.front()) {
                    deque1.pop_front();
                }
                if (nums[j] == deque2.front()) {
                    deque2.pop_front();
                }
                if (j == 0) {
                    t.remove(0);
                } else {
                    t.remove(prefix[j - 1]);
                }
                j++;
            }
            int a = t.findMax(prefix[i]);
            t.add(prefix[i]);
            res = max(res, a);
        }
        return res;
    }
};

int main() {
    string problemName = "3845";
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
        auto res = sol.maxXor(nums, k);
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