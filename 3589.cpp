#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 5e4;
const int NUM = 5e4;
bool prime[NUM + 1];
bool isInit = false;
static void init() {
    if (isInit) return;
    for (int i = 2; i <= NUM; i++) {
        prime[i] = true;
    }
    prime[1] = false;
    int nsqrt = sqrt(NUM);
    for (int i = 2; i <= nsqrt; i++) {
        if (prime[i]) {
            for (int j = i + i; j <= NUM; j += i) {
                prime[j] = false;
            }
        }
    }
    isInit = true;
}
int minDeque[N];
int maxDeque[N];

class Solution {
   public:
    int primeSubarray(vector<int>& nums, int k) {
        init();
        int n = nums.size();
        int i = 0;
        int iforward = 0;
        int c = 0;
        int cforward = 0;
        int minl = 0;
        int minr = -1;
        int maxl = 0;
        int maxr = -1;
        int res = 0;
        int preIndex = -1;
        for (int j = 0; j < n; j++) {
            if (prime[nums[j]]) {
                c++;
                cforward++;
                while (minr >= minl && minDeque[minr] > nums[j]) {
                    minr--;
                }
                minDeque[++minr] = nums[j];
                while (maxr >= maxl && maxDeque[maxr] < nums[j]) {
                    maxr--;
                }
                maxDeque[++maxr] = nums[j];
            }
            if (c < 2) continue;
            int diff = maxDeque[maxl] - minDeque[minl];
            while (diff > k) {
                if (nums[i] == minDeque[minl]) {
                    minl++;
                    diff = maxDeque[maxl] - minDeque[minl];
                } else if (nums[i] == maxDeque[maxl]) {
                    maxl++;
                    diff = maxDeque[maxl] - minDeque[minl];
                }
                c -= prime[nums[i]];
                i++;
                iforward = i;
                cforward = c;
            }
            if (c < 2) continue;
            while (cforward >= 2) {
                if (prime[nums[iforward]]) {
                    cforward--;
                }
                iforward++;
            }
            res += (iforward - i);
        }
        return res;
    }
};

int main() {
    string problemName = "Q3";
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
        auto res = sol.primeSubarray(nums, k);
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