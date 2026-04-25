#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 1e5;
int avail[N];
int evenCnt[N];
class Solution {
   public:
    vector<int> kthRemainingInteger(vector<int>& nums,
                                    vector<vector<int>>& queries) {
        int n = nums.size();
        int q = queries.size();
        int c = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i] % 2 == 0) {
                c++;
            }
            avail[i] = nums[i] / 2 - c;
            evenCnt[i] = c;
        }
        vector<int> res(q);
        for (int i = 0; i < q; i++) {
            int l = queries[i][0];
            int r = queries[i][1];
            int k = queries[i][2];
            int d = 0;
            if (l > 0) {
                d = evenCnt[l - 1];
            }
            int x = -1;
            while (l <= r) {
                int mid = (l + r) >> 1;
                if (avail[mid] + d < k) {
                    l = mid + 1;
                } else {
                    x = mid;
                    r = mid - 1;
                }
            }
            if (x == -1) {
                r = queries[i][1];
                res[i] = (k - avail[r] - d) * 2 + nums[r];
                if (res[i] % 2 == 1) {
                    res[i]--;
                }
            } else {
                res[i] = nums[x] - 2 - (avail[x] + d - k) * 2;
                if (res[i] % 2 == 1) {
                    res[i]++;
                }
            }
        }
        return res;
    }
};

int main() {
    string problemName = "3911";
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
        auto queries = jread_vector2d(line_in);
        auto res = sol.kthRemainingInteger(nums, queries);
        getline(file_out, line_out);
        auto ans = jread_vector(line_out);
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