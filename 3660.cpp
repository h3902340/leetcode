#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Data {
    int v;
    int l;
    int r;
};
const int N = 1e5;
Data arr[N];
int pre[N];
class Solution {
   public:
    vector<int> maxValue(vector<int>& nums) {
        int n = nums.size();
        int j = -1;
        int mx = 0;
        for (int i = 0; i < n; i++) {
            int v = nums[i];
            int l = i;
            int r = i;
            int a = (j >= 0 && arr[j].v > v) ? arr[j].v : v;
            while (j >= 0 && arr[j].v > v) {
                l = arr[j].l;
                j--;
            }
            arr[++j] = {a, l, r};
            mx = max(mx, v);
            pre[i] = mx;
        }
        vector<int> res(n);
        int k = 0;
        for (int i = 0; i < n; i++) {
            if (i > arr[k].r) {
                k++;
            }
            res[i] = pre[arr[k].r];
        }
        return res;
    }
};

int main() {
    string problemName = "3660";
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
        auto res = sol.maxValue(nums);
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