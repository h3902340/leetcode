#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
const int N = 1e5;
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

class Solution {
   public:
    long long countSubarrays(vector<int>& nums, long long k) {
        int n = nums.size();
        deque1.init();
        deque2.init();
        int j = 0;
        int l = 0;
        ll res = 0;
        for (int i = 0; i < n; i++) {
            while (!deque1.empty() && deque1.back() < nums[i]) {
                deque1.pop_back();
            }
            deque1.push(nums[i]);
            while (!deque2.empty() && deque2.back() > nums[i]) {
                deque2.pop_back();
            }
            deque2.push(nums[i]);
            l++;
            ll cost = (ll)(deque1.front() - deque2.front()) * l;
            while (cost > k) {
                if (nums[j] == deque1.front()) {
                    deque1.pop_front();
                }
                if (nums[j] == deque2.front()) {
                    deque2.pop_front();
                }
                j++;
                l--;
                cost = (ll)(deque1.front() - deque2.front()) * l;
            }
            res += l;
        }
        return res;
    }
};

int main() {
    string problemName = "3835";
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
        auto k = jread_longlong(line_in);
        auto res = sol.countSubarrays(nums, k);
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