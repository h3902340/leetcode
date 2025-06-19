#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 1000;
int up[N - 1];
int down[N];
int temp[N];
class Solution {
   public:
    int minimumMountainRemovals(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            temp[i] = nums[i];
        }
        int i = 0;
        up[0] = 1;
        for (int j = 1; j < n - 1; j++) {
            if (nums[i] < nums[j]) {
                i++;
                nums[i] = nums[j];
            } else if (nums[i] > nums[j]) {
                int l = 0;
                int r = i;
                int max = -1;
                while (l <= r) {
                    int mid = (l + r) >> 1;
                    if (nums[mid] > nums[j]) {
                        r = mid - 1;
                    } else if (nums[mid] == nums[j]) {
                        max = mid - 1;
                        break;
                    } else {
                        max = mid;
                        l = mid + 1;
                    }
                }
                nums[max + 1] = nums[j];
            }
            up[j] = i + 1;
        }
        i = n - 1;
        down[n - 1] = 1;
        for (int j = n - 2; j >= 1; j--) {
            if (temp[j] > temp[i]) {
                i--;
                temp[i] = temp[j];
            } else if (temp[j] < temp[i]) {
                int l = i;
                int r = n - 1;
                int min = n;
                while (l <= r) {
                    int mid = (l + r) >> 1;
                    if (temp[j] < temp[mid]) {
                        l = mid + 1;
                    } else if (temp[j] == temp[mid]) {
                        min = mid + 1;
                        break;
                    } else {
                        min = mid;
                        r = mid - 1;
                    }
                }
                temp[min - 1] = temp[j];
            }
            down[j] = n - i;
        }
        int res = n;
        for (int i = 1; i < n - 1; i++) {
            // reason why this is correct:
            // The minimal removals must happen when i is the peak of both
            // sides. For example, if 1,2,3,...,10,...,i,...,3,2,1, then when
            // i=10, the up[i]+down[i] is bigger than the former because the
            // peak is counted twice. And because i is the shared peak, the
            // up[i] and down[i] must be greater than 1 to form a valid
            // mountain.
            if (up[i] <= 1 || down[i] <= 1) continue;
            int a = n - up[i] - down[i] + 1;
            if (res > a) {
                res = a;
            }
        }
        return res;
    }
};

int main() {
    string problemName = "1671";
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
        auto res = sol.minimumMountainRemovals(nums);
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