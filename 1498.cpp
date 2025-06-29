#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int MOD = 1e9 + 7;
const int N = 1e5;
int twoPower[N];
bool isInit = false;
static void init() {
    if (isInit) return;
    twoPower[0] = 1;
    for (int i = 1; i < N; i++) {
        twoPower[i] = twoPower[i - 1] << 1;
        if (twoPower[i] >= MOD) {
            twoPower[i] -= MOD;
        }
    }
    isInit = true;
}
class Solution {
   public:
    int numSubseq(vector<int>& nums, int target) {
        init();
        int n = nums.size();
        sort(nums.begin(), nums.end());
        int res = 0;
        for (int i = 0; i < n; i++) {
            int a = target - nums[i];
            int l = i;
            int r = n - 1;
            int max = -1;
            while (l <= r) {
                int mid = (l + r) >> 1;
                if (nums[mid] > a) {
                    r = mid - 1;
                } else {
                    max = mid;
                    l = mid + 1;
                }
            }
            if (max == -1) break;
            res += twoPower[max - i];
            if (res >= MOD) {
                res -= MOD;
            }
        }
        return res;
    }
};

int main() {
    string problemName = "1498";
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
        auto target = jread_int(line_in);
        auto res = sol.numSubseq(nums, target);
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