#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Data {
    int end;
    int val;
};
const int N = 1e6;
vector<Data> pre = vector<Data>(N);
vector<Data> cur = vector<Data>(N);
class Solution {
   public:
    int maxValue(vector<vector<int>>& events, int k) {
        int n = events.size();
        auto cmp = [](vector<int>& a, vector<int>& b) { return a[1] < b[1]; };
        sort(events.begin(), events.end(), cmp);
        int totalMax = 0;
        for (int i = 0; i < n; i++) {
            int end = events[i][1];
            int val = events[i][2];
            totalMax = max(totalMax, val);
            pre[i] = {end, totalMax};
        }
        for (int j = 1; j < k; j++) {
            totalMax = 0;
            for (int i = 0; i < n; i++) {
                int start = events[i][0];
                int end = events[i][1];
                int val = events[i][2];
                int l = 0;
                int r = i - 1;
                int upper = -1;
                while (l <= r) {
                    int mid = (l + r) >> 1;
                    if (pre[mid].end < start) {
                        upper = mid;
                        l = mid + 1;
                    } else {
                        r = mid - 1;
                    }
                }
                if (upper != -1) {
                    val += pre[upper].val;
                }
                totalMax = max(totalMax, val);
                cur[i] = {end, totalMax};
            }
            swap(pre, cur);
        }
        return pre[n - 1].val;
    }
};

int main() {
    string problemName = "1751";
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
        auto events = jread_vector2d(line_in);
        getline(file_in, line_in);
        auto k = jread_int(line_in);
        auto res = sol.maxValue(events, k);
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