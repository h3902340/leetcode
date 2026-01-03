#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
#define lg2(n) (31 - __builtin_clz(n))
struct Data {
    int i;
    int j;
    int v;
};
const int U_MIN = 0;
const int U_MAX = 1e9;
const int N = 5e4;
const int LGN = lg2(N) + 1;
const auto cmp = [](Data& a, Data& b) { return a.v < b.v; };
int rmq[N][LGN];
int rmq2[N][LGN];
void init(vector<int>& arr, int n) {
    int lgn = lg2(n);
    for (int i = 0; i < n; i++) {
        rmq[i][0] = arr[i];
        rmq2[i][0] = arr[i];
    }
    int k = 1;
    for (int l = 1; l <= lgn; l++) {
        int cap = n - (k << 1) + 1;
        for (int i = 0; i < cap; i++) {
            rmq[i][l] = max(rmq[i][l - 1], rmq[i + k][l - 1]);
            rmq2[i][l] = min(rmq2[i][l - 1], rmq2[i + k][l - 1]);
        }
        k <<= 1;
    }
}
int findMax(int i, int j) {
    int k = lg2(j - i + 1);
    return max(rmq[i][k], rmq[j - (1 << k) + 1][k]);
}
int findMin(int i, int j) {
    int k = lg2(j - i + 1);
    return min(rmq2[i][k], rmq2[j - (1 << k) + 1][k]);
}

class Solution {
   public:
    long long maxTotalValue(vector<int>& nums, int k) {
        int n = nums.size();
        init(nums, n);
        priority_queue<Data, vector<Data>, decltype(cmp)> pq(cmp);
        int mx = U_MIN - 1;
        int mn = U_MAX + 1;
        for (int i = 0; i < n; i++) {
            mx = max(mx, nums[i]);
            mn = min(mn, nums[i]);
            pq.push({0, i, mx - mn});
        }
        ll res = 0;
        while (k > 0) {
            Data t = pq.top();
            pq.pop();
            res += t.v;
            if (t.i < t.j) {
                t.i++;
                t.v = findMax(t.i, t.j) - findMin(t.i, t.j);
                pq.push(t);
            }
            k--;
        }
        return res;
    }
};

int main() {
    string problemName = "3691";
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
        auto res = sol.maxTotalValue(nums, k);
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