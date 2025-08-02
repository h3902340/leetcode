#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
const int BUCKET_SIZE = 256;
const int MASK = 255;
int buckets[BUCKET_SIZE];
void radixSort(vector<int>& nums, int n) {
    vector<int> temp(n);
    for (int j = 0; j < 32; j += 8) {
        for (auto& e : nums) {
            buckets[(e >> j) & MASK]++;
        }
        for (int i = 1; i < BUCKET_SIZE; i++) {
            buckets[i] += buckets[i - 1];
        }
        for (int i = n - 1; i >= 0; i--) {
            temp[--buckets[(nums[i] >> j) & MASK]] = nums[i];
        }
        fill(begin(buckets), end(buckets), 0);
        nums.swap(temp);
    }
}

class Solution {
   public:
    long long minCost(vector<int>& basket1, vector<int>& basket2) {
        int n = basket1.size();
        radixSort(basket1, n);
        radixSort(basket2, n);
        int c = min(basket1[0], basket2[0]) << 1;
        int i = 0;
        int j = 0;
        int x = 0;
        int y = 0;
        while (i < n || j < n) {
            int a = 0;
            if (i == n) {
                a = basket2[j];
            } else {
                if (j == n) {
                    a = basket1[i];
                } else {
                    a = min(basket1[i], basket2[j]);
                }
            }
            int b = 0;
            int c = 0;
            while (i < n && basket1[i] == a) {
                b++;
                i++;
            }
            while (j < n && basket2[j] == a) {
                c++;
                j++;
            }
            if (b == c) {
                continue;
            }
            if ((b + c) & 1) {
                return -1;
            }
            if (b < c) {
                int d = (c - b) >> 1;
                for (int k = 0; k < d; k++) {
                    basket2[y] = a;
                    y++;
                }
            } else {
                int d = (b - c) >> 1;
                for (int k = 0; k < d; k++) {
                    basket1[x] = a;
                    x++;
                }
            }
        }
        ll res = 0;
        int l1 = 0;
        int l2 = 0;
        for (int i = 0; i < x; i++) {
            int a = basket1[l1];
            int b = basket2[l2];
            if (c < a && c < b) {
                res += (ll)c * (x - i);
                break;
            }
            if (a < b) {
                res += a;
                l1++;
            } else {
                res += b;
                l2++;
            }
        }
        return res;
    }
};

int main() {
    string problemName = "2561";
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
        auto basket1 = jread_vector(line_in);
        getline(file_in, line_in);
        auto basket2 = jread_vector(line_in);
        auto res = sol.minCost(basket1, basket2);
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