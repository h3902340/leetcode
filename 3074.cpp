#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int U = 50;
int cnt[U + 1];

class Solution {
   public:
    int minimumBoxes(vector<int>& apple, vector<int>& capacity) {
        int n = apple.size();
        int m = capacity.size();
        int a = 0;
        for (int i = 0; i < n; i++) {
            a += apple[i];
        }
        int ma = 0;
        int mi = U + 1;
        for (int i = 0; i < m; i++) {
            cnt[capacity[i]]++;
            ma = max(ma, capacity[i]);
            mi = min(mi, capacity[i]);
        }
        int res = 0;
        for (int i = ma; i >= mi; i--) {
            int d = (a + i - 1) / i;
            if (cnt[i] < d) {
                a -= cnt[i] * i;
                res += cnt[i];
            } else {
                res += d;
                break;
            }
        }
        for (int i = 0; i < m; i++) {
            cnt[capacity[i]] = 0;
        }
        return res;
    }
};

int main() {
    string problemName = "3074";
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
        auto apple = jread_vector(line_in);
        getline(file_in, line_in);
        auto capacity = jread_vector(line_in);
        auto res = sol.minimumBoxes(apple, capacity);
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