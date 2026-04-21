#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int U = 5e4;
const int Usqrt = 224;
bool isInit = false;
int prime[Usqrt];
int sz;
void init() {
    prime[0] = 0;
    prime[1] = 0;
    for (int i = 2; i < Usqrt; i++) {
        prime[i] = 1;
    }
    for (int i = 2; i * i < Usqrt; i++) {
        if (prime[i]) {
            for (int j = i + i; j < Usqrt; j += i) {
                prime[j] = 0;
            }
        }
    }
    sz = 0;
    for (int i = 2; i < Usqrt; i++) {
        if (prime[i]) {
            prime[sz++] = i;
        }
    }
}

class Solution {
   public:
    int countGoodSubseq(vector<int>& nums, int p,
                        vector<vector<int>>& queries) {
        if (!isInit) {
            init();
            isInit = true;
        }
        int n = nums.size();
        int q = queries.size();
        int mask = 0;
        for (int i = 0; i < n; i++) {
            mask ^= i;
        }
        unordered_map<int, int> cnt;
        unordered_map<int, int> x;
        unordered_map<int, int> fre;
        int a = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i] % p == 0) {
                a++;
                int b = nums[i] / p;
                for (int j = 0; j < sz; j++) {
                    if (b % prime[j] == 0) {
                        fre[cnt[prime[j]]]--;
                        cnt[prime[j]]++;
                        fre[cnt[prime[j]]]++;
                        x[prime[j]] ^= i;
                    }
                    while (b % prime[j] == 0) {
                        b /= prime[j];
                    }
                }
                if (b > 1) {
                    fre[cnt[b]]--;
                    cnt[b]++;
                    fre[cnt[b]]++;
                    x[b] ^= i;
                }
            }
        }
        int res = 0;
        for (int i = 0; i < q; i++) {
            int ind = queries[i][0];
            int val = queries[i][1];
            if (nums[ind] % p == 0) {
                a--;
                int b = nums[ind] / p;
                for (int j = 0; j < sz; j++) {
                    if (b % prime[j] == 0) {
                        fre[cnt[prime[j]]]--;
                        cnt[prime[j]]--;
                        fre[cnt[prime[j]]]++;
                        x[prime[j]] ^= ind;
                    }
                    while (b % prime[j] == 0) {
                        b /= prime[j];
                    }
                }
                if (b > 1) {
                    fre[cnt[b]]--;
                    cnt[b]--;
                    fre[cnt[b]]++;
                    x[b] ^= ind;
                }
            }
            if (val % p == 0) {
                a++;
                int b = val / p;
                for (int j = 0; j < sz; j++) {
                    if (b % prime[j] == 0) {
                        fre[cnt[prime[j]]]--;
                        cnt[prime[j]]++;
                        fre[cnt[prime[j]]]++;
                        x[prime[j]] ^= ind;
                    }
                    while (b % prime[j] == 0) {
                        b /= prime[j];
                    }
                }
                if (b > 1) {
                    fre[cnt[b]]--;
                    cnt[b]++;
                    fre[cnt[b]]++;
                    x[b] ^= ind;
                }
            }
            nums[ind] = val;
            if (a > 0) {
                bool ok = fre[a] == 0;
                if (ok && n <= 7 && a == n) {
                    vector<bool> se(n);
                    int c = n;
                    for (auto& e : cnt) {
                        if (e.second == n - 1) {
                            int idx = x[e.first] ^ mask;
                            if (se[idx] == 0) {
                                se[idx] = 1;
                                c--;
                                if (c == 0) {
                                    break;
                                }
                            }
                        }
                    }
                    if (c == 0) {
                        ok = false;
                    }
                }
                if (ok) {
                    res++;
                }
            }
        }
        return res;
    }
};

int main() {
    string problemName = "3901";
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
        auto p = jread_int(line_in);
        getline(file_in, line_in);
        auto queries = jread_vector2d(line_in);
        auto res = sol.countGoodSubseq(nums, p, queries);
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