#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Data {
    int val;
    int cnt;
};
const int N = 1e5;
Data tmp[N];
const int BUCKET_SIZE = 256;
const int MASK = 255;
int buckets[BUCKET_SIZE];
vector<int> temp(N);
void radixSort(vector<int>& nums) {
    int n = nums.size();
    for (int j = 0; j < 32; j += 8) {
        for (int i = 0; i < n; i++) {
            buckets[(nums[i] >> j) & MASK]++;
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
    int maxFrequency(vector<int>& nums, int k, int numOperations) {
        int n = nums.size();
        radixSort(nums);
        int i = 0;
        int sz = 0;
        while (i < n) {
            int val = nums[i];
            int cnt = 1;
            i++;
            while (i < n && nums[i] == val) {
                cnt++;
                i++;
            }
            tmp[sz++] = {val, cnt};
        }
        int k2 = k << 1;
        i = 0;
        int j = 0;
        int cnt = 0;
        int res = 0;
        for (; i < sz; i++) {
            Data& a = tmp[i];
            int cap = INT32_MAX;
            if (INT32_MAX - k2 > a.val) {
                cap = a.val + k2;
            }
            while (j < sz && tmp[j].val <= cap) {
                cnt += tmp[j].cnt;
                if (cnt >= numOperations) {
                    res = numOperations;
                    break;
                }
                j++;
            }
            if (cnt >= numOperations) {
                break;
            }
            if (res < cnt) {
                res = cnt;
            }
            if (j == sz) {
                break;
            }
            cnt -= tmp[i].cnt;
        }
        i = 0;
        int l = 0;
        int r = 0;
        cnt = 0;
        for (; i < sz; i++) {
            int capL = tmp[i].val - k;
            int capR = tmp[i].val + k;
            while (l < i && tmp[l].val < capL) {
                cnt -= tmp[l].cnt;
                l++;
            }
            while (r < sz && tmp[r].val <= capR) {
                cnt += tmp[r].cnt;
                r++;
            }
            int a = min(numOperations, cnt - tmp[i].cnt) + tmp[i].cnt;
            if (res < a) {
                res = a;
            }
        }
        return res;
    }
};

int main() {
    string problemName = "3346";
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
        auto numOperations = jread_int(line_in);
        auto res = sol.maxFrequency(nums, k, numOperations);
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