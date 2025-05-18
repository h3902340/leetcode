#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int NMAX = 1e5;
const int DMAX = 82;
vector<int> fre[DMAX];
int sums[NMAX];
int cnt[DMAX];
class Solution {
   public:
    int minSwaps(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < DMAX; i++) {
            fre[i].clear();
        }
        for (int i = 0; i < n; i++) {
            int ori = nums[i];
            int s = 0;
            while (ori > 0) {
                s += ori % 10;
                ori /= 10;
            }
            fre[s].push_back(nums[i]);
            sums[i] = s;
        }
        int ans = 0;
        cnt[0] = 0;
        for (int i = 1; i < DMAX; i++) {
            sort(fre[i].begin(), fre[i].end());
            cnt[i] = fre[i].size() + cnt[i - 1];
        }
        int i = 0;
        int a = 0;
        while (a < n) {
            int j = 0;
            while (j < fre[i].size()) {
                if (nums[a] != fre[i][j]) {
                    int s = sums[a];
                    int l = 0;
                    int r = fre[s].size() - 1;
                    int b = -1;
                    while (l <= r) {
                        int mid = (l + r) >> 1;
                        if (fre[s][mid] > nums[a]) {
                            r = mid - 1;
                        } else if (fre[s][mid] < nums[a]) {
                            l = mid + 1;
                        } else {
                            b = cnt[s - 1] + mid;
                            break;
                        }
                    }
                    swap(nums[a], nums[b]);
                    swap(sums[a], sums[b]);
                    ans++;
                } else {
                    j++;
                    a++;
                }
            }
            i++;
        }
        return ans;
    }
};

int main() {
    string problemName = "3551";
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
        jprint_vector(nums, "nums");
        auto res = sol.minSwaps(nums);
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
        jprint_int(res, "res");
        jprint_int(ans, "ans");
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