#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

// same as 2866
#define ll long long
struct Data {
    int v;
    int cnt;
};
const int N = 1e5;
ll up[N];
ll down[N];
Data st[N];
class Solution {
   public:
    long long maximumSumOfHeights(vector<int>& maxHeights) {
        int n = maxHeights.size();
        int r = -1;
        ll sum = 0;
        for (int i = 0; i < n; i++) {
            int c = 1;
            while (r >= 0 && st[r].v > maxHeights[i]) {
                sum = sum - (ll)(st[r].v - maxHeights[i]) * st[r].cnt;
                c += st[r].cnt;
                r--;
            }
            st[++r] = {maxHeights[i], c};
            sum += maxHeights[i];
            up[i] = sum;
        }
        r = -1;
        sum = 0;
        for (int i = n - 1; i >= 0; i--) {
            int c = 1;
            while (r >= 0 && st[r].v > maxHeights[i]) {
                sum = sum - (ll)(st[r].v - maxHeights[i]) * st[r].cnt;
                c += st[r].cnt;
                r--;
            }
            st[++r] = {maxHeights[i], c};
            sum += maxHeights[i];
            down[i] = sum;
        }
        ll res = 0;
        for (int i = 0; i < n; i++) {
            ll a = up[i] + down[i] - maxHeights[i];
            if (res < a) {
                res = a;
            }
        }
        return res;
    }
};

int main() {
    string problemName = "2865";
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
        auto maxHeights = jread_vector(line_in);
        auto res = sol.maximumSumOfHeights(maxHeights);
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