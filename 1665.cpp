#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Task {
    int actual;
    int diff;
};
const auto cmp = [](Task& a, Task& b) { return a.diff < b.diff; };
const int N = 1e5;
Task arr[N];
class Solution {
   public:
    int minimumEffort(vector<vector<int>>& tasks) {
        int n = tasks.size();
        for (int i = 0; i < n; i++) {
            arr[i] = {tasks[i][0], tasks[i][1] - tasks[i][0]};
        }
        sort(begin(arr), begin(arr) + n, cmp);
        int l = 0;
        int res = 0;
        for (int i = n - 1; i >= 0; i--) {
            l += arr[i].actual;
            res = max(res, l + arr[i].diff);
        }
        return res;
    }
};

int main() {
    string problemName = "1665";
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
        auto tasks = jread_vector2d(line_in);
        auto res = sol.minimumEffort(tasks);
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