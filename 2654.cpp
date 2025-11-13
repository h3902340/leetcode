#include <iostream>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int Usqrt = 1e3;
const int Usqrtsqrt = 31;
const int N = 50;
int prime[Usqrt + 1];
bool isInit = false;
int SZ = 0;
static void init() {
    for (int i = 2; i <= Usqrt; i++) {
        prime[i] = 1;
    }
    for (int i = 2; i <= Usqrtsqrt; i++) {
        if (prime[i] == 1) {
            int cap = Usqrt / i;
            for (int j = 2; j <= cap; j++) {
                prime[i * j] = 0;
            }
        }
    }
    for (int i = 2; i <= Usqrt; i++) {
        if (prime[i] == 1) {
            prime[SZ++] = i;
        }
    }
}

vector<int> factor[N];
unordered_map<int, int> cnt;
// sliding window, time: O(NlogU), space: O(NlogU), excluding prime table and
// hash table
class Solution {
   public:
    int minOperations(vector<int>& nums) {
        if (!isInit) {
            init();
            isInit = true;
        }
        int n = nums.size();
        int one = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i] == 1) {
                one++;
            }
            factor[i].clear();
        }
        if (one > 0) {
            return n - one;
        }
        cnt.clear();
        int k = 0;
        int best = n + 1;
        for (int i = 0; i < n; i++) {
            int e = nums[i];
            nums[i] = 0;
            for (int j = 0; j < SZ; j++) {
                int p = prime[j];
                if (p * p > e) {
                    break;
                }
                if (e % p == 0) {
                    factor[i].push_back(p);
                    if (cnt[p] > 0) {
                        nums[cnt[p] - 1]--;
                    }
                    cnt[p]++;
                    nums[cnt[p] - 1]++;
                    while (e % p == 0) {
                        e /= p;
                    }
                }
                if (e == 1) {
                    break;
                }
            }
            if (e > 1) {
                factor[i].push_back(e);
                if (cnt[e] > 0) {
                    nums[cnt[e] - 1]--;
                }
                cnt[e]++;
                nums[cnt[e] - 1]++;
            }
            int temp = 0;
            if (nums[i - k] == 0) {
                temp = i - k + 2;
            }
            while (nums[i - k] == 0) {
                for (auto& f : factor[k]) {
                    nums[cnt[f] - 1]--;
                    cnt[f]--;
                    if (cnt[f] > 0) {
                        nums[cnt[f] - 1]++;
                    }
                }
                k++;
                temp--;
            }
            if (temp != 0 && best > temp) {
                best = temp;
            }
        }
        if (best == n + 1) {
            return -1;
        }
        return n + best - 2;
    }
};

int main() {
    string problemName = "2654";
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
        auto res = sol.minOperations(nums);
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