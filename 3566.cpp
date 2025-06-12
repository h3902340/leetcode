#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Node {
    int used;
    long long quot;
    int index;
};
const int NMAX = 12;
Node q[1 << (NMAX + 1)];

class Solution {
   public:
    bool checkEqualPartitions(vector<int>& nums, long long target) {
        int n = nums.size();
        int l = 0;
        int r = 0;
        int i = 0;
        while (i < n && target % nums[i] != 0) {
            i++;
        }
        if (i == n) return false;
        q[r] = {1 << i, target / nums[i], i};
        r++;
        while (l < r) {
            int f = q[l].used;
            long long f_quot = q[l].quot;
            int f_index = q[l].index;
            l++;
            if (f_quot == 1) {
                long long tmp = target;
                for (int i = 0; i < n; i++) {
                    if (!(f & (1 << i))) {
                        if (tmp % nums[i] != 0) return false;
                        tmp /= nums[i];
                    }
                }
                if (tmp > 1) {
                    return false;
                }
                return true;
            }
            if (f_quot == 0) continue;
            for (int i = f_index + 1; i < n; i++) {
                int m = 1 << i;
                if (!(f & m)) {
                    if (f_quot % nums[i] != 0) continue;
                    q[r].used = f | m;
                    q[r].quot = f_quot / nums[i];
                    q[r].index = i;
                    r++;
                }
            }
        }
        return false;
    }
};

int main() {
    string problemName = "3566";
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
        auto target = jread_longlong(line_in);
        auto res = sol.checkEqualPartitions(nums, target);
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