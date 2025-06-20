#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
const int MOD = 1e9 + 7;
const int N = 3e4;
struct Data {
    int v;
    int cnt;
};
Data st[N];
class Solution {
   public:
    int sumSubarrayMins(vector<int>& arr) {
        int n = arr.size();
        ll res = 0;
        int sum = 0;
        int r = -1;
        for (int i = 0; i < n; i++) {
            int c = 1;
            while (r >= 0 && st[r].v >= arr[i]) {
                sum = sum - (st[r].v - arr[i]) * st[r].cnt;
                c += st[r].cnt;
                r--;
            }
            st[++r] = {arr[i], c};
            sum += arr[i];
            res += sum;
            if (res >= MOD) {
                res -= MOD;
            }
        }
        return res;
    }
};

int main() {
    string problemName = "907";
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
        auto arr = jread_vector(line_in);
        auto res = sol.sumSubarrayMins(arr);
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