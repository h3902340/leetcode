#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int U = 1e5;
int arr[U * 2 + 2];
class Solution {
   public:
    int minMoves(vector<int>& nums, int limit) {
        int n = nums.size();
        int h = n / 2;
        for (int i = 0; i < h; i++) {
            arr[2] += 2;
            arr[limit * 2 + 1] -= 2;
            int a = min(nums[i], nums[n - 1 - i]);
            int b = max(nums[i], nums[n - 1 - i]);
            arr[a + 1]--;
            arr[b + limit + 1]++;
            arr[a + b]--;
            arr[a + b + 1]++;
        }
        int res = INT32_MAX;
        int cur = 0;
        for (int i = 2; i <= limit * 2; i++) {
            cur += arr[i];
            res = min(res, cur);
            arr[i] = 0;
        }
        arr[limit * 2 + 1] = 0;
        return res;
    }
};

int main() {
    string problemName = "1674";
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
        int limit = jread_int(line_in);
        auto res = sol.minMoves(nums, limit);
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